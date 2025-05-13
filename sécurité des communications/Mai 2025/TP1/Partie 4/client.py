'''
JEMAI Axel
PERROT Jean
TD3/TP6
'''
import requests
import rsa


#proxies pour simuler une attaque MITM
proxies = {
    "http": "http://127.0.0.1:8080",
    "https": "http://127.0.0.1:8080"
}


(C_pub, C_priv) = rsa.newkeys(512)  # 512 bits pour la démonstration

#Message à chiffrer
message = "Salut Serveur!"
signed_message = rsa.sign(message.encode('utf-8'), C_priv, 'SHA-256')

#Récupérer la clé publique du serveur
response = requests.get('http://localhost:5000/public_key',proxies=proxies)
key_data = response.json()
S_pub = rsa.PublicKey(n=key_data['n'], e=key_data['e'])

#Chiffrer le message avec la clé publique du serveur
crypted_message = rsa.encrypt(message.encode('utf-8'), S_pub)


#Envoyer en json la clé publique du client et le message chiffré et le message signé
response = requests.post('http://localhost:5000/decrypt', json={
    'message_signed': signed_message.hex(),
    'message_crypted': crypted_message.hex(),
    'public_key': {
        'n': C_pub.n,
        'e': C_pub.e
    }
},proxies=proxies)

print("Réponse du serveur :", response.json())