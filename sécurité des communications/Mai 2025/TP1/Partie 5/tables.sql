-- Créer la base de données
CREATE DATABASE IF NOT EXISTS anochat;
USE anochat;

-- Table des utilisateurs
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    pseudo VARCHAR(50) NOT NULL UNIQUE,
    password TEXT NOT NULL, -- en clair pour le moment
    avatar_url TEXT, -- lien vers le PNG
    public_key TEXT NOT NULL,
    private_key TEXT NOT NULL
);

-- Table des messages
CREATE TABLE IF NOT EXISTS messages (
    id INT AUTO_INCREMENT PRIMARY KEY,
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    message TEXT NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (receiver_id) REFERENCES users(id) ON DELETE CASCADE
);
