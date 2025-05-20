from flask import Flask, request, jsonify, send_file
import threading
import sys
import logging
from werkzeug.serving import WSGIRequestHandler
import requests


class QuietHandler(WSGIRequestHandler):
    def log_request(self, code='-', size='-'):
        pass


app = Flask(__name__)
messages = []

@app.route("/")
def index():
    return send_file("index.html")

@app.route("/send", methods=["POST"])
def send():
    data = request.get_json()
    msg = data.get("message")
    sender = data.get("from", "Alice")
    forwarded = data.get("forwarded", False)

    if msg:
        entry = {"text": msg, "from": sender}
        messages.append(entry)
        print(f"[{sender}] {msg}")

        # Relayer uniquement si pas encore relayé
        if not forwarded:
            try:
                requests.post("http://127.0.0.1:5002/send", json={
                    "message": msg,
                    "from": sender,
                    "forwarded": True
                })
            except requests.exceptions.RequestException as e:
                print(f"Erreur en envoyant à Bob: {e}")

    return "OK"


@app.route("/messages")
def get_messages():
    return jsonify(messages[-50:])


def terminal_input():
    while True:
        try:
            msg = input()
            formatted = f"[Alice] {msg}"
            messages.append(formatted)
            try:
                requests.post("http://127.0.0.1:5002/send", json={"message": formatted})
            except requests.exceptions.RequestException as e:
                print(f"Erreur en envoyant à Bob: {e}")
        except KeyboardInterrupt:
            break

if __name__ == "__main__":
    threading.Thread(target=terminal_input, daemon=True).start()
    from werkzeug.serving import run_simple
    run_simple("127.0.0.1", 5001, app, request_handler=QuietHandler, use_reloader=False)
