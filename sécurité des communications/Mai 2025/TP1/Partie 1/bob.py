import socket
from sympy import randprime
from Cryptodome.Util import number
import random


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
p = number.getPrime(2048) # p est un nombre premier
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


input("[Bob] Appuyez sur Entrée pour fermer la connexion...")
client.close()
print("[Bob] Connexion fermée.")

