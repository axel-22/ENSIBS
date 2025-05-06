import socket
import math

# Création du socket serveur
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)

print("[Alice] En attente d'une connexion...")

conn, addr = server.accept()
print(f"[Alice] Bob connecté depuis {addr}")

# --- Le reste du programme ---
p = 23
a = 8
g = 7
A_pkey = g**a%p

# Envoi de la clé publique A à Bob
conn.send(str(A_pkey).encode())
print(f"[Alice] Clé publique envoyée : {A_pkey}")

# Réception de la clé publique B de Bob
B_pkey = int(conn.recv(1024).decode())
print(f"[Alice] Clé publique reçue de Bob : {B_pkey}")

# Calcul de la clé secrète partagée
AB_key = B_pkey**a%p
print(f"[Alice] Clé partagée : {AB_key}")

input("[Alice] Appuyez sur Entrée pour fermer la connexion...")
print("[Alice] Connexion fermée.")
conn.close()
server.close()

