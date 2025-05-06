import socket
from sympy import randprime
from Cryptodome.Random import get_random_bytes
from Cryptodome.Util import number
import random
import hashlib
import json

# Création du socket serveur
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)

print("[Alice] En attente d'une connexion...")

conn, addr = server.accept()
print(f"[Alice] Bob connecté depuis {addr}")


p = number.getPrime(128) # p est un nombre premier
a = random.randint(2, p-1) # a est un nombre aléatoire
g = 2
A_pkey = pow(g, a, p) # calcul de g**a%p

# Envoi de la clé publique A à Bob
conn.send(str(p).encode())
print(f"[Alice] Nombre premier envoyé : {p}")
conn.send(str(A_pkey).encode())
print(f"[Alice] Clé publique envoyée : {A_pkey}")

# Réception de la clé publique B de Bob
B_pkey = int(conn.recv(1024).decode())
print(f"[Alice] Clé publique reçue de Bob : {B_pkey}")

# Calcul de la clé secrète partagée
AB_key = pow(B_pkey, a, p) # calcul B_pkey**a%p
print(f"[Alice] Clé partagée : {AB_key}")

# Génération d'une clé AES
aes_key = get_random_bytes(16)  # 128 bits
print(f"[Alice] Clé AES générée : {aes_key}")

AB_key_bytes = AB_key.to_bytes(16, 'big')

# XOR octet par octet
aes_shared_key = b''
# On boucle sur les octets de la clé AES et de la clé partagée
for a, b in zip(aes_key, AB_key_bytes):
    aes_shared_key += bytes([a ^ b])

print(f"[Alice] Clé partagée chiffrée avec Bob : {aes_shared_key}")

# Calcul du hash SHA-256 de la clé AES
sha256_hash = hashlib.sha256(aes_key).hexdigest()
print(f"[Alice] Hash SHA-256 de la clé AES : {sha256_hash}")
keys = {
    'aes_shared_key': aes_shared_key.hex(),
    'hash': sha256_hash
}
# Conversion du dictionnaire en JSON
keys_json = json.dumps(keys)

# Envoi du dictionnaire converti en JSON (en bytes)
conn.send(keys_json.encode())

ack_alice = conn.recv(1024)
ack_decrypted = b''
for a, b in zip(ack_alice, aes_key):
    ack_decrypted += bytes([a ^ b])

message = ack_decrypted.decode('utf-8')  # Là tu peux faire decode
print(f"[Alice] Message de Bob : {message}")

input("[Alice] Appuyez sur Entrée pour fermer la connexion...")
print("[Alice] Connexion fermée.")
conn.close()
server.close()
