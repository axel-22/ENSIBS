# Dossiers
SRC_DIR = src
BIN_DIR = bin

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Trouver tous les fichiers .c
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Transformer chaque .c en exécutable
EXECS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

# Compilation principale : génère tous les exécutables
all: $(EXECS)

# Règle de compilation pour chaque exécutable
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Création du dossier bin si nécessaire
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage des fichiers compilés
clean:
	rm -rf $(BIN_DIR)

# Supprime tout et recompile
re: clean all

.PHONY: all clean re
