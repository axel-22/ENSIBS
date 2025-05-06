import socket
from sympy import randprime
from Cryptodome.Util import number
import random
import json
import hashlib

# Création du socket client
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    client.connect(('localhost', 12345))
except ConnectionRefusedError:
    print("[Bob] Erreur : Assurez-vous que Alice est lancé avant Bob.")
    exit()

# Récupération des informations de connexion
local_ip, local_port = client.getsockname()
remote_ip, remote_port = client.getpeername()

print("[Bob] Connecté à Alice.")

print(f"[Bob] Adresse locale : {local_ip}:{local_port}")
print(f"[Bob] Alice est connectée sur : {remote_ip}:{remote_port}")

# --- Le reste du programme ---
p = int(client.recv(1024).decode()) # p est un nombre premier reçu d'Alice
b = random.randint(2, p-1) # a est un nombre aléatoire
g = 2
B_pkey = pow(g, b, p) # calcul de  g**b%p 

# Réception de la clé publique d'Alice
A_pkey = int(client.recv(1024).decode())
print(f"[Bob] Clé publique reçue d'Alice : {A_pkey}")

# Envoi de la clé publique de Bob
client.send(str(B_pkey).encode())
print(f"[Bob] Clé publique envoyée : {B_pkey}")

# Calcul de la clé partagée
AB_key = pow(A_pkey, b, p) # calcul A_pkey**b%p
print(f"[Bob] Clé partagée : {AB_key}")

receive_keys = client.recv(1024)
print(f"[Bob] Clé partagée chiffrée avec Alice : {receive_keys}")

keys = json.loads(receive_keys)

# Récupérer la clé partagée chiffrée et le hash de la clé AES
aes_shared_key_received = bytes.fromhex(keys['aes_shared_key'])  # Convertir la clé reçue en bytes

AB_key_bytes = AB_key.to_bytes(16, 'big') # On convertit la clé partagée en bytes

aes_key = b''
for a, b in zip(aes_shared_key_received, AB_key_bytes):
    aes_key += bytes([a ^ b])
    
print(f"[Bob] Clé aes : {aes_key}")
received_hash = keys['hash']

# Calculer le hash SHA-256 de la clé partagée chiffrée reçue
calculated_hash = hashlib.sha256(aes_key).hexdigest()

# Vérifier l'intégrité
if calculated_hash == received_hash:
    print("[Bob] L'intégrité de la clé chiffrée a été vérifiée avec succès.")
    # Message de confirmation
    message = "Bien reçu !"
    message_bytes = message.encode('utf-8') # Convertir le message en bytes
    # chiffrer le message avec la clé AES
    aes_ack= b''
    for a, b in zip(aes_key, message_bytes):
        aes_ack += bytes([a ^ b])
    client.send(aes_ack)
else:
    print("[Bob] ERREUR : L'intégrité de la clé chiffrée a échoué. La clé pourrait avoir été modifiée.")

input("[Bob] Appuyez sur Entrée pour fermer la connexion...")
client.close()
print("[Bob] Connexion fermée.")

