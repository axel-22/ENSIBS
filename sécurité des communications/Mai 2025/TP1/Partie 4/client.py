from flask import Flask, request, jsonify, send_file, session
import threading
import sys
import logging
from werkzeug.serving import WSGIRequestHandler
import requests
import rsa
import base64
import os
from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes

# Handler silencieux
class QuietHandler(WSGIRequestHandler):
    def log_request(self, code='-', size='-'):
        pass

# Vérification des arguments
if len(sys.argv) != 3:
    print("Usage: python3 client.py <port> <name>")
    sys.exit(1)

port = int(sys.argv[1])
name = sys.argv[2]

# Définir l'adresse du contact distant
other_port = 5001 if port == 5002 else 5002
other_url = f"http://127.0.0.1:{other_port}/send"

(public_key, private_key) = rsa.newkeys(1024)  #Genérer les clés publique et privée


app = Flask(__name__)
app.secret_key = os.urandom(16)
messages = []
aes_keys = {} 

# Envoi de la clé publique au contact distant localhost 5000
def send_public_key(public_key, name ):
    try:
        requests.post("http://127.0.0.1:5000/public_key", json={
            "public_key": {
                "n": public_key.n,
                "e": public_key.e
            },
            "name": name
        })
        print("Clé rsa envoyé avec succes")
    except requests.exceptions.RequestException as e:
        print(f"Erreur en envoyant la clé publique à {other_url}: {e}")
        sys.exit(1)

send_public_key(public_key, name)

@app.route("/")
def index():
    return send_file("index.html")



def aes_encrypt(msg: str, key: bytes) -> str:
    message_bytes = msg.encode()
    nonce = get_random_bytes(12)  # Taille recommandée pour GCM
    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    ciphertext, tag = cipher.encrypt_and_digest(message_bytes)

    # Encodage Base64 de nonce + tag + ciphertext pour transport
    combined = nonce + tag + ciphertext
    return base64.b64encode(combined).decode()

def aes_decrypt(ciphertext_b64: str, key: bytes) -> str:
    combined = base64.b64decode(ciphertext_b64)
    nonce = combined[:12]
    tag = combined[12:28]
    ciphertext = combined[28:]

    cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
    decrypted = cipher.decrypt_and_verify(ciphertext, tag)
    return decrypted.decode()




aes_key = None  # Variable globale unique par instance

@app.route("/aes_signed", methods=["POST"])
def decrypt_message():
    global aes_key
    data = request.json
    try:
        aes_signed_b64 = data['aes_key']
        encrypted_aes_bytes = base64.b64decode(aes_signed_b64)
        aes_key = rsa.decrypt(encrypted_aes_bytes, private_key)

        sender = data.get("from", None)
        print(f"[{name}] Clé AES reçue et déchiffrée pour {sender if sender else name} : {aes_key.hex()}")
        return "OK"
    except Exception as e:
        return f"Erreur lors du déchiffrement de la clé AES : {e}", 400


@app.route("/send", methods=["POST"])
def send():
    global aes_key
    data = request.get_json()
    raw_msg = data.get("message")
    sender = data.get("from", name)
    forwarded = data.get("forwarded", False)

    print(f"[{name}] Traitement message de '{sender}': {raw_msg}")

    msg_encrypted = None
    msg_clear = None

    if sender.lower() == name.lower():
        # Envoi d'un message par cette instance
        if aes_key:
            try:
                msg_encrypted = aes_encrypt(raw_msg, aes_key)
                msg_clear = raw_msg
                print(f"[{name}] -> Message clair avant chiffrement : {msg_clear}")
                print(f"[{name}] -> Message chiffré envoyé : {msg_encrypted}")
            except Exception as e:
                print(f"[{name}] Erreur de chiffrement AES : {e}")
                msg_encrypted = "[Erreur de chiffrement]"
                msg_clear = raw_msg
        else:
            print(f"[{name}] -> Pas de clé AES, message envoyé en clair.")
            msg_encrypted = raw_msg
            msg_clear = raw_msg
    else:
        # Réception d'un message d'une autre instance
        msg_encrypted = raw_msg
        if aes_key:
            try:
                msg_clear = aes_decrypt(msg_encrypted, aes_key)
                print(f"[{name}] <- Message chiffré reçu : {msg_encrypted}")
                print(f"[{name}] <- Message déchiffré reçu : {msg_clear}")
            except Exception as e:
                print(f"[{name}] Erreur de déchiffrement AES : {e}")
                msg_clear = "[Erreur de déchiffrement]"
        else:
            print(f"[{name}] <- Message chiffré reçu : {msg_encrypted}")
            print(f"[{name}] <- Pas de clé AES pour déchiffrer.")
            msg_clear = "[Clé AES manquante]"

    messages.append({
        "text": msg_clear,
        "from": sender
    })

    if not forwarded:
        try:
            requests.post(other_url, json={
                "message": msg_encrypted,
                "from": sender,
                "forwarded": True
            })
        except requests.exceptions.RequestException as e:
            print(f"[{name}] Erreur en transmettant à {other_url}: {e}")

    return "OK"



@app.route("/messages")
def get_messages():
    return jsonify(messages[-50:])

def terminal_input():
    while True:
        try:
            msg = input()
            try:
                requests.post("http://127.0.0.1:{}/send".format(port), json={
                    "message": msg,
                    "from": name,
                    "forwarded": False
                })
            except requests.exceptions.RequestException as e:
                print(f"Erreur en envoyant à {other_url}: {e}")
        except KeyboardInterrupt:
            break


if __name__ == "__main__":
    threading.Thread(target=terminal_input, daemon=True).start()
    from werkzeug.serving import run_simple
    run_simple("127.0.0.1", port, app, request_handler=QuietHandler, use_reloader=False)
