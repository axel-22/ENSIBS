import requests
import rsa

#Récupérer la clé publique du serveur
response = requests.get('http://localhost:5000/public_key')
key_data = response.json()

#Reconstituer la clé publique
server_public_key = rsa.PublicKey(n=key_data['n'], e=key_data['e'])

#Message à chiffrer
message = "Bonjour, serveur RSA!"
encrypted_message = rsa.encrypt(message.encode('utf-8'), server_public_key)

#Envoyer le message chiffré (en hexadécimal)
response = requests.post('http://localhost:5000/decrypt', json={
    'message': encrypted_message.hex()
})

print("Réponse du serveur :", response.json())