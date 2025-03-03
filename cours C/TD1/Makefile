# Définition du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Dossiers
SRC_DIR = src
BIN_DIR = bin

# Nom de l'exécutable
TARGET = $(BIN_DIR)/exo1

# Fichiers sources
SRC = $(SRC_DIR)/exo1.c

# Règle principale
all: $(TARGET)

# Compilation
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(TARGET)

# Nettoyage complet
mrproper: clean
	rm -rf $(BIN_DIR)/*

# Indique à Make que "clean" et "mrproper" ne sont pas des fichiers
.PHONY: all clean mrproper
