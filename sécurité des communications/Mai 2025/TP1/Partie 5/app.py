'''
JEMAI Axel
PERROT Jean
TD3/TP6
'''
from flask import Flask, request, jsonify, json, render_template, flash, redirect, url_for, session
from flask_socketio import SocketIO, send, emit, join_room
import rsa
import mysql.connector
import config  # ton fichier config.py
app = Flask(__name__)
app.secret_key = 'super_secret_key' 
app.debug = True
socketio = SocketIO(app)
app.jinja_env.auto_reload = True
app.config['TEMPLATES_AUTO_RELOAD'] = True


def get_db_connection():
    return mysql.connector.connect(
        host=config.DB_HOST,
        port=config.DB_PORT,
        user=config.DB_USER,
        password=config.DB_PASSWORD,
        database=config.DB_NAME
    )


@app.route('/send', methods=['POST'])
def send():
    data = request.get_json()
    messages.append(data)
    return '', 204

@app.route('/receive', methods=['GET'])
def receive():
    return jsonify(messages)

#Générer les clés publique et privée
(public_key, private_key) = rsa.newkeys(512)  # 512 bits pour la démonstration


@app.route('/')
def home():
    return render_template('home.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        login = request.form['login']
        password = request.form['password']

        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)

        # Vérifier si l'utilisateur existe déjà
        query = "SELECT * FROM users WHERE pseudo = %s"
        cursor.execute(query, (login,))
        user = cursor.fetchone()

        if user:
            flash('Utilisateur déjà existant !', 'danger')
        else:
            # Vérifier si les mots de passe sont identiques
            if password != request.form['confirm']:
                flash('Les mots de passe ne correspondent pas !', 'danger')
            else:
                # Insérer le nouvel utilisateur
                avatar = request.form['avatar']
                avatar_url = None
                if avatar is not None:
                    avatar_url = 'https://bootdey.com/img/Content/avatar/'+avatar
                else:
                    avatar_url = 'https://bootdey.com/img/Content/avatar/avatar1.png'
                (public_key, private_key) = rsa.newkeys(2048)
                # Convertir les clés en chaînes de caractères
                publicpem = public_key.save_pkcs1().decode('utf-8')
                privatepem = private_key.save_pkcs1().decode('utf-8')   
                insert_query = "INSERT INTO users (pseudo, password, avatar_url, public_key, private_key) VALUES (%s, %s, %s, %s, %s)"
                cursor.execute(insert_query, (login, password, avatar_url, publicpem, privatepem))
                conn.commit()
                flash('Inscription réussie, vous pouvez vous connecter.', 'success')
                # Fermer la connexion
                cursor.close()
                conn.close()
                return redirect(url_for('login'))
            return redirect(url_for('register'))

        cursor.close()
        conn.close()

    return render_template('register.html')



@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        login = request.form['login']
        password = request.form['password']

        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)

        # On recherche un utilisateur avec ce login ET ce password
        query = "SELECT * FROM users WHERE pseudo = %s AND password = %s"
        cursor.execute(query, (login, password))
        user = cursor.fetchone()

        cursor.close()
        conn.close()

        if user:
            session['user'] = login
            session['avatar'] = user['avatar_url']
            session['user_id'] = user['id'] 
            flash('Connexion réussie !', 'success')
            return redirect(url_for('messaging'))  # ou autre page
        else:
            flash('Identifiants incorrects', 'danger')

    return render_template('login.html')

@app.route('/messaging')
def messaging():
    if 'user' not in session:
        flash('Veuillez vous connecter pour accéder au chat.', 'warning')
        return redirect(url_for('login'))    

    conn = get_db_connection()
    cursor = conn.cursor(dictionary=True)
    query="SELECT pseudo, avatar_url FROM users where pseudo != %s"
    cursor.execute(query, (session['user'],))
    users = cursor.fetchall()
    print(users)
    cursor.close()
    conn.close()

    return render_template('chat.html', username=session['user'], avatar=session['avatar'], user_id=session['user_id']  , users=users)


@app.route('/users')
def list_users():  # <-- nouveau nom ic
    conn = get_db_connection()
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT id, pseudo, avatar_url FROM users")
    users = cursor.fetchall()
    cursor.close()
    conn.close()
    return jsonify(users)


@socketio.on('join_room')
def handle_join_room(data):
    user_id = data.get('user_id')
    if user_id:
        join_room(str(user_id))
        print(f"User {user_id} joined their personal room", flush=True)

# @app.route("/messages/<username>", methods=["GET", "POST"])
# def get_messages(username):
#     # Exemple : messages fictifs, à adapter selon ta base de données
#     if request.method == 'GET':
#         messages = [
#             {"sender": "eve", "receiver": "alice", "content": "Salut Alice", "timestamp": "2025-05-19 10:00"},
#             {"sender": "alice", "receiver": "eve", "content": "Salut Eve", "timestamp": "2025-05-19 10:05"},
#         ]
#         # Filtre selon l'utilisateur concerné (ou tout autre logique)
#         user_messages = [msg for msg in messages if username in (msg["sender"], msg["receiver"])]
#         return jsonify(user_messages)
#     elif request.method == 'POST':
#         data = request.get_json()
#         print("data")
#         print(data)
#         # Traite et stocke le message ici (dans ta BDD)
#         # Par exemple, insérer dans la base de données messages
#         return '', 204

@app.route("/messages/<username>", methods=["GET"])
def get_messages(username):
    if 'user_id' not in session:
        return jsonify([])

    current_user_id = session['user_id']

    conn = get_db_connection()
    cursor = conn.cursor(dictionary=True)

    # Récupérer l'id de l'utilisateur cible (celui avec qui on discute)
    cursor.execute("SELECT id FROM users WHERE pseudo = %s", (username,))
    user = cursor.fetchone()
    if not user:
        return jsonify([])

    other_user_id = user['id']

    # Récupérer les messages avec les pseudos associés
    query = """
        SELECT 
            u1.pseudo AS sender,
            u2.pseudo AS receiver,
            m.message,
            m.timestamp
        FROM messages m
        JOIN users u1 ON m.sender_id = u1.id
        JOIN users u2 ON m.receiver_id = u2.id
        WHERE (m.sender_id = %s AND m.receiver_id = %s)
           OR (m.sender_id = %s AND m.receiver_id = %s)
        ORDER BY m.timestamp ASC
    """
    cursor.execute(query, (current_user_id, other_user_id, other_user_id, current_user_id))
    messages = cursor.fetchall()

    cursor.close()
    conn.close()
    print("messages existant : ", messages, flush=True)

    return jsonify(messages)



@socketio.on('send_message')
def handle_send_message(data):
    print("ok from socketio", flush=True)
    try:
        sender = session.get('user_id')
        receiver_username = data.get('to')
        message_text = data.get('content')
        print("data : ", data, flush=True)

        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)  # ← tu veux des dicts ici
        query = "SELECT id FROM users WHERE pseudo = %s"
        cursor.execute(query, (receiver_username,))
        receiver = cursor.fetchone()
        receiver_id = receiver["id"] if receiver else None

        if not receiver_id:
            print("Aucun utilisateur trouvé pour :", receiver_username, flush=True)
            return {'status': 'error', 'error': 'Utilisateur non trouvé'}
        print("the message : ", message_text, flush=True)
        print(f"Message envoyé par {sender} à {receiver_username} (ID: {receiver_id})", flush=True)
        print(f"Message reçu du client via websocket: {message_text} pour {receiver_username}", flush=True)

        cursor.execute(
            "INSERT INTO messages (sender_id, receiver_id, message) VALUES (%s, %s, %s)",
            (sender, receiver_id, message_text)
        )
        conn.commit()
        cursor.close()
        conn.close()

        emit('receive_message', {
            'from': session.get('user'),
            'message': message_text
        }, room=str(receiver_id))


        # Envoie aussi à l’expéditeur (pour affichage immédiat)
        emit('receive_message', {
            'from': session.get('user'),
            'message': message_text
        }, room=str(sender))  # <- ici on réutilise la session pour trouver le socket sender


        return {'status': 'ok'}

    except Exception as e:
        print("data erreur : ", data, flush=True)
        print("Erreur dans handle_send_message:", repr(e), flush=True)  # plus clair que str(e)
        return {'status': 'error', 'error': str(e)}




@app.route("/logout", methods=["POST"])
def logout():
    session.clear()  # Supprime toutes les données de session
    return redirect(url_for("home"))  # Redirige vers la page d'acceuil

socketio.run(app, debug=True, host='0.0.0.0', port=5000, allow_unsafe_werkzeug=True)