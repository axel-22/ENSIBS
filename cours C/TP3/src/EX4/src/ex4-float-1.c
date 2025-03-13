/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP3 - Exercice 3 - Comparaison de deux décimaux avec un type int
 */
#include <stdio.h>

// Fonction de comparaison
int compare(float a, float b) {
    int ret;
    if (a == b) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

int demander_nombre() {
    float nombre;
    float input;
    char term;
    do {
        printf("Entrez un nombre décimal : ");
        input = scanf("%f%c", &nombre, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || term != '\n');

    return nombre;
}

int main() {
    float x, y;
    x = demander_nombre();
    y = demander_nombre();
    int c = compare(x, y);
    if (c) {
        printf("Les deux décimaux sont égaux: %d.\n", c);
    } else {
        printf("Les deux décimaux sont différents: %d.\n", c);
    }

    return 0;
} 