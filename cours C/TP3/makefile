# Liste des sous-dossiers contenant un Makefile
SUBDIRS := $(wildcard src/*)

# Cible principale : compile tous les sous-projets
all:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/makefile ]; then \
			$(MAKE) -C $$dir; \
		fi \
	done

# Nettoyage dans tous les sous-projets
clean:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/makefile ]; then \
			$(MAKE) -C $$dir clean; \
		fi \
	done

# Nettoyage complet et recompilation
re: clean all

.PHONY: all clean re
