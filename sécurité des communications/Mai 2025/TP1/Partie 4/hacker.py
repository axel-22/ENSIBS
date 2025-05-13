from mitmproxy import http
import json
import rsa

S_pub = None

def response(flow: http.HTTPFlow):
    global S_pub
    if flow.request.path == "/public_key" and flow.response.status_code == 200:
        try:
            data = json.loads(flow.response.content)
            S_pub = rsa.PublicKey(n=data['n'], e=data['e'])
        except Exception as e:
            print("Erreur lors de l’analyse de la réponse :", e)

def request(flow: http.HTTPFlow):
    global S_pub
    if flow.request.path == "/decrypt" and flow.request.method == "POST":
        try:
            # Générer une nouvelle paire de clés pour le hacker
            (H_pub, H_priv) = rsa.newkeys(512)

            message = "Salut Hacker!"
            signed_message = rsa.sign(message.encode('utf-8'), H_priv, 'SHA-256')
            crypted_message = rsa.encrypt(message.encode('utf-8'), S_pub)

            original = json.loads(flow.request.content)
            print("[!] Requête interceptée, modification en cours...")
            # Remplacer la clé publique du client par celle du hacker
            original["public_key"] = {
                "n": H_pub.n,
                "e": H_pub.e
            }
            # Remplacer le message chiffré et signé par ceux du hacker
            original["message_crypted"] = crypted_message.hex()
            original["message_signed"] = signed_message.hex()

            flow.request.content = json.dumps(original).encode('utf-8')
            print("Modification envoyée.")
        except Exception as e:
            print("Erreur lors de la modification : ", e)
