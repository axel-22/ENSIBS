'''
JEMAI Axel
PERROT Jean
TD3/TP6
'''
from flask import Flask, request, jsonify, json
import rsa
import os

app = Flask(__name__)
app.debug = True

@app.route('/public_key', methods=['POST'])
def get_public_key():
    data = request.json
    name = data['name']
    n = data['public_key']['n']
    e = data['public_key']['e']

    print("clé de", name, "n =", n)
    print("clé de", name, "e =", e)

    # Créer le répertoire 'key' s'il n'existe pas
    os.makedirs("key", exist_ok=True)

    # Écrire la clé publique dans un fichier nommé selon 'name'
    file_path = os.path.join("key", name)
    with open(file_path, "w") as f:
        f.write(f"{n}\n{e}\n")

    return "Clé publique enregistrée", 200



@app.route('/encrypt_aes', methods=['POST'])
def decrypt_message():
    code = 400
    try:
        signed_message = bytes.fromhex(request.json['message_signed'])  # Récupérer le message signé
        C_pub = rsa.PublicKey(n=request.json['public_key']['n'], e=request.json['public_key']['e']) # Récupérer la clé publique du client
        crypted_message = bytes.fromhex(request.json['message_crypted'])  # Récupérer le message chiffré
        decrypted = rsa.decrypt(crypted_message, private_key)  # Déchiffrer le message chiffré
        isValid = rsa.verify(decrypted, signed_message ,C_pub)  # Vérifier la signature
        ack = "Accepter"
        code = 200
            
    except Exception as e:
        if str(e) == "Verification failed":
            ack = "Rejeter"
        else:
            return jsonify({'error': str(e)}), code
    retobject = {
        'msg': decrypted.decode('utf-8'),  # Convertir le message déchiffré en chaîne de caractères
        'ack': ack
    }
    return jsonify(retobject), code

app.run(port=5000)