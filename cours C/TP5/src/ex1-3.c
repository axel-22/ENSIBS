#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *px;
    
    // Allocation de mémoire pour un int
    px = (int *) malloc(sizeof(int));

    // Vérification de malloc
    if (px == NULL) {
        printf("Échec de l'allocation mémoire\n");
        return 1;
    }

    *px = 1;

    // Affichage des adresses et valeurs
    printf("Adresse de px : %p\n", (void*)&px);
    printf("Adresse pointee par px : %p\n", (void*)px);
    printf("Valeur mémorisée à l'adresse pointée par px : %d\n", *px);

    // Libération de la mémoire allouée
    free(px);

    return 0;
}
