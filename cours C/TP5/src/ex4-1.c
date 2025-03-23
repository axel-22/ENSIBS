/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP5 - Exercice 4 - Pointeurs et structures
 */
#define N 3
#include <stdio.h>
#include <stdlib.h>

typedef struct maillon {
    int x;
    struct maillon *suiv;
} maillon;

int main(void) {
    maillon lc;
    lc.x = 1;
    printf("Valeur du champ x = %d\n\n", lc.x);

    lc.suiv = (maillon *) malloc(sizeof(maillon));  // Allocation d'un deuxième maillon
    if (lc.suiv == NULL) {  // Vérification de malloc
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }

    lc.suiv->x = 2;
    lc.suiv->suiv = NULL;  // Initialiser le pointeur suivant

    printf("Valeur du champ x du deuxième maillon = %d\n\n", lc.suiv->x);

    free(lc.suiv);  // Libération de la mémoire allouée

    return 0;
}
