from flask import Flask, request, jsonify
import rsa

app = Flask(__name__)

#Générer les clés publique et privée
(public_key, private_key) = rsa.newkeys(512)  # 512 bits pour la démonstration

@app.route('/public_key', methods=['GET'])
def get_public_key():
    return jsonify({
        'n': public_key.n,
        'e': public_key.e
    })

@app.route('/decrypt', methods=['POST'])
def decrypt_message():
    try:
        encrypted = bytes.fromhex(request.json['message'])  # message hexadécimal
        decrypted = rsa.decrypt(encrypted, private_key).decode('utf-8')
        return jsonify({'decrypted_message': decrypted})
    except Exception as e:
        return jsonify({'error': str(e)}), 400

app.run(port=5000)