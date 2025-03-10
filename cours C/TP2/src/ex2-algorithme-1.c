#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30
#define MAX_VALUE 50

// Fonction pour afficher le tableau
void afficher_tableau(int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

// Tri à bulles
void tri_bulles(int tab[], int taille) {
    int temp, permut;
    do {
        permut = 0;
        for (int i = 0; i < taille - 1; i++) {
            if (tab[i] > tab[i + 1]) {
                temp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = temp;
                permut = 1;
            }
        }
    } while (permut);
}



int main() {
    int tab[N];
    srand(time(NULL));

    // Remplissage aléatoire du tableau
    for (int i = 0; i < N; i++) {
        tab[i] = rand() % (MAX_VALUE + 1);
    }

    printf("Tableau original:\n");
    afficher_tableau(tab, N);

    // Tri à bulles
    int tab_bulles[N];
    for (int i = 0; i < N; i++) tab_bulles[i] = tab[i];
    tri_bulles(tab_bulles, N);
    printf("\nTableau trié par tri à bulles:\n");
    afficher_tableau(tab_bulles, N);

    return 0;
}