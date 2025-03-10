#include <stdio.h>

// Fonction de comparaison
int compare(int a, int b) {
    int ret;
    if (a == b) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}


int demander_nombre() {
    int nombre;
    int input;
    do {
        printf("Entrez un nombre entier:\n ");
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
    int x, y;
    x = demander_nombre();
    y = demander_nombre();
    int c = compare(x, y);
    if (c) {
        printf("Les deux entiers sont égaux: %d.\n", c);
    } else {
        printf("Les deux entiers sont différents: %d.\n", c);
    }

    return 0;
} 