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

// Tri par insertion
void tri_insertion(int tab[], int taille) {
    for (int i = 1; i < taille; i++) {
        int val = tab[i];
        int j = i - 1;
        while (j >= 0 && tab[j] > val) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = val;
    }
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

    // Tri par insertion
    int tab_insertion[N];
    for (int i = 0; i < N; i++) tab_insertion[i] = tab[i];
    tri_insertion(tab_insertion, N);
    printf("\nTableau trié par insertion:\n");
    afficher_tableau(tab_insertion, N);

    return 0;
}