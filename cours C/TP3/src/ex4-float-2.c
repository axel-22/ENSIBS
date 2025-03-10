#include <stdio.h>

// Fonction de comparaison
int compare(int a, int b) {
    char c;
    if (a == b) {
        c = 'V';
    } else {
        c = 'F';
    }
    return c;
}


int demander_nombre() {
    int nombre;
    float input;
    do {
        printf("Entrez un nombre décimal:\n ");
        input = scanf("%d", &nombre);
        // Vérifier si scanf a bien lu un entier
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 1);

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