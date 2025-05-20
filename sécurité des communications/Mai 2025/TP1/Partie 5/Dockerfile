# Dockerfile

FROM python:3.11-slim

WORKDIR /app

# Installer les dépendances système nécessaires (mysql client libs)
RUN apt-get update && apt-get install -y default-libmysqlclient-dev gcc && rm -rf /var/lib/apt/lists/*

# Copier requirements si tu en as, sinon installer directement
COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Copier tout le code de l'app (le volume dans docker-compose fera l'override en dev)
COPY . .

# Variables d'environnement Flask
ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0
# active le mode debug & reload
ENV FLASK_ENV=development 

EXPOSE 5000

CMD ["python", "app.py"]
