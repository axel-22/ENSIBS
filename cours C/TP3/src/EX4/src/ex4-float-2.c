/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP3 - Exercice 3 - Comparaison de deux décimaux avec un type char
 */

#include <stdio.h>
// Fonction de comparaison
char compare(int a, int b) {
    char c;
    if (a == b) {
        c = 'V';
    } else {
        c = 'F';
    }
    return c;
}


int demander_nombre() {
    float nombre;
    float input;
    char term;
    do {
        printf("Entrez un nombre décimal : ");
        input = scanf("%d%c", &nombre, &term);
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
    if (c == 'V') {
        printf("Les deux décimaux sont égaux: %c.\n", c);
    } else {
        printf("Les deux décimaux sont différents: %c.\n", c);
    }

    return 0;
} 