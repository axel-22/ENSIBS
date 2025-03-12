# Dossiers
SRC_DIR = src
BIN_DIR = bin

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lm

# Trouver tous les fichiers .c
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Générer les fichiers objets correspondants
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Identifier les fichiers modules (sans main) qui ne doivent pas être compilés seuls en exécutable
MODULES = $(BIN_DIR)/ex5-degre.o

# Générer la liste des exécutables valides (sans les modules)
EXECS = $(filter-out $(MODULES), $(OBJS:.o=))

# Compilation principale : génère tous les exécutables SAUF les modules
all: $(BIN_DIR)/ex5-testdegre1 $(BIN_DIR)/ex5-testdegre2

# Compilation des fichiers .c en .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation de ex5-testdegre1 en le liant avec ex5-degre.o
$(BIN_DIR)/ex5-testdegre1: $(BIN_DIR)/ex5-testdegre1.o $(BIN_DIR)/ex5-degre.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compilation de ex5-testdegre2 en le liant avec ex5-degre.o
$(BIN_DIR)/ex5-testdegre2: $(BIN_DIR)/ex5-testdegre2.o $(BIN_DIR)/ex5-degre.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Création du dossier bin si nécessaire
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage des fichiers compilés
clean:
	rm -rf $(BIN_DIR)

# Supprime tout et recompile
re: clean all

.PHONY: all clean re
