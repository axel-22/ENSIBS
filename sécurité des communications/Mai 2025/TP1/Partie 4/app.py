'''
JEMAI Axel
PERROT Jean
TD3/TP6
'''

from flask import Flask, request, jsonify
import rsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import padding, rsa as crypto_rsa
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend
import secrets
import base64
import requests
import os

app = Flask(__name__)
app.debug = False

@app.route('/public_key', methods=['POST'])
def get_public_key():
    data = request.json
    name = data['name']
    n = int(data['public_key']['n'])
    e = int(data['public_key']['e'])

    print(f"Clé de {name} - n = {n}")
    print(f"Clé de {name} - e = {e}")

    # Utilise RSAPublicNumbers depuis cryptography (pas rsa)
    public_numbers = crypto_rsa.RSAPublicNumbers(e, n)
    public_key = public_numbers.public_key(default_backend())

    # Créer le répertoire 'key' s'il n'existe pas
    os.makedirs("key", exist_ok=True)

    # Chemin du fichier .pem
    file_path = os.path.join("key", f"{name}.pem")

    # Écrire la clé au format PEM
    with open(file_path, "wb") as f:
        f.write(
            public_key.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            )
        )

    return f"Clé publique enregistrée dans {file_path}", 200


def send_aes_key():
    try:
        aes_key = secrets.token_bytes(32)  # Clé AES 256 bits
        key_dir = "key"
        if not os.path.exists(key_dir):
            raise FileNotFoundError(f"Le répertoire '{key_dir}' est introuvable.")

        pem_files = [f for f in os.listdir(key_dir) if f.endswith(".pem")]

        if not pem_files:
            raise ValueError("Aucune clé publique disponible dans le répertoire 'key'.")

        # Trier les fichiers par date de modification (du plus ancien au plus récent)
        pem_files.sort(key=lambda f: os.path.getmtime(os.path.join(key_dir, f)))

        print(f"Clé AES générée : {aes_key.hex()}")

        # Envoi chaque clé à un port commençant à 5001 + index
        base_port = 5001
        for i, filename in enumerate(pem_files):
            port = base_port + i
            send_to_port(filename, port, aes_key, key_dir)

    except Exception as e:
        print(f"[ERREUR] lors de l'envoi de la clé AES : {e}")
        raise

def send_to_port(filename, port, aes_key, key_dir):
    try:
        pem_path = os.path.join(key_dir, filename)
        with open(pem_path, "rb") as f:
            public_key = serialization.load_pem_public_key(f.read(), backend=default_backend())
        numbers = public_key.public_numbers()
        n = numbers.n
        e = numbers.e
        S_pub = rsa.PublicKey(n, e)
        encrypted_aes = rsa.encrypt(aes_key, S_pub)
        encrypted_aes_b64 = base64.b64encode(encrypted_aes).decode()
        url = f"http://127.0.0.1:{port}/aes_signed"
        response = requests.post(url, json={"aes_key": encrypted_aes_b64})
        response.raise_for_status()
        print(f"Clé AES envoyée à {filename} via {url} - Code {response.status_code}")
    except Exception as e:
        print(f"Erreur lors de l'envoi à {url} : {e}")


if __name__ == "__main__":
    try:
        send_aes_key()
    except Exception as e:
        print("")
        print("**********************************************************************************")
        print(f"[ERREUR] lors de l'envoi de la clé AES : {e}")
        print("Erreur Normal tant que Alice et BOB n'ont pas envoyé leur clé publique au serveur")
        print("Ordre de lancement : serveur, Alice, Bob")
        print("puis relancer le serveur")
        print("**********************************************************************************")
        print("")

    app.run(port=5000)
