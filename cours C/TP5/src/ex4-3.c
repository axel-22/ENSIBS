/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP5 - Exercice 4-3 - Liste chaînée de maillons
 */
#include <stdio.h>
#include <stdlib.h>

#define N 5 // Définition du nombre de maillons

// Définition de la structure Maillon
typedef struct Maillon {
    int x;
    struct Maillon *suiv;
} Maillon;

// Fonction pour créer une liste chaînée de N maillons
Maillon* creerListe(int n) {
    Maillon *tete = NULL, *lc = NULL;
    for (int i = 0; i < n; i++) {
        Maillon *nouveau = (Maillon*) malloc(sizeof(Maillon));
        if (!nouveau) {
            perror("Erreur d'allocation mémoire");
            exit(EXIT_FAILURE);
        }
        nouveau->x = i;
        nouveau->suiv = NULL;
        if (tete == NULL) {
            tete = nouveau;
        } else {
            lc->suiv = nouveau;
        }
        lc = nouveau;
    }
    return tete;
}

// Fonction pour afficher la liste chaînée
void afficherListe(Maillon *tete) {
    Maillon *lc = tete;
    while (lc != NULL) {
        printf("[%d] -> ", lc->x);
        lc = lc->suiv;
    }
    printf("NULL\n");
}

// Fonction pour supprimer un maillon sans briser le chaînage
Maillon* supprimerMaillon(Maillon *tete, int pos) {
    if (tete == NULL) return NULL;
    
    Maillon *lc = tete, *precedent = NULL;
    int index = 0;
    
    // Cas particulier : suppression du premier maillon
    if (pos == 0) {
        tete = tete->suiv;
        free(lc);
        return tete;
    }
    
    // Parcours de la liste jusqu'à trouver le maillon à supprimer
    while (lc != NULL && index < pos) {
        precedent = lc;
        lc = lc->suiv;
        index++;
    }
    
    // Si la position est invalide
    if (lc == NULL) {
        printf("Position invalide !\n");
        return tete;
    }
    
    // Suppression du maillon
    precedent->suiv = lc->suiv;
    free(lc);
    return tete;
}

// Fonction pour libérer la mémoire de la liste chaînée
void libererListe(Maillon *tete) {
    Maillon *lc;
    while (tete != NULL) {
        lc = tete;
        tete = tete->suiv;
        free(lc);
    }
}

int main() {
    Maillon *tete = creerListe(N);
    afficherListe(tete);
    
    int pos;
    int input;
    char term;
    do {
        printf("Entrez la position du maillon à supprimer : ");
        input = scanf("%d%c", &pos, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || pos < 0 || pos > 4 || term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || pos < 0 || pos > 4 || term != '\n');
    
    tete = supprimerMaillon(tete, pos);
    afficherListe(tete);
    
    libererListe(tete);
    return 0;
}
