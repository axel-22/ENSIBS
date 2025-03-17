# Dossiers
SRC_DIR = src
BIN_DIR = bin

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lm

# Fichier source commun (librairie)
LIB_SRC = $(SRC_DIR)/ex5-degre.c

# Trouver les fichiers tests (qui contiennent le main)
TEST_SRCS = $(filter-out $(LIB_SRC), $(wildcard $(SRC_DIR)/*.c))

# Exécutables correspondants
EXECS = $(TEST_SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

all: $(EXECS)

# Compilation de chaque test avec la librairie
$(BIN_DIR)/%: $(SRC_DIR)/%.c $(LIB_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Créer le dossier bin si nécessaire
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage
clean:
	rm -rf $(BIN_DIR)

# Supprime tout et recompile
re: clean all

.PHONY: all clean re
