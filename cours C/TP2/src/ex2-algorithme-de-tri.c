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

// Tri par recherche de minima successifs
void tri_selection(int tab[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < taille; j++) {
            if (tab[j] < tab[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = tab[i];
            tab[i] = tab[min_index];
            tab[min_index] = temp;
        }
    }
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

    // Tri à bulles
    int tab_bulles[N];
    for (int i = 0; i < N; i++) tab_bulles[i] = tab[i];
    tri_bulles(tab_bulles, N);
    printf("\nTableau trié par tri à bulles:\n");
    afficher_tableau(tab_bulles, N);

    // Tri par sélection
    int tab_selection[N];
    for (int i = 0; i < N; i++) tab_selection[i] = tab[i];
    tri_selection(tab_selection, N);
    printf("\nTableau trié par sélection:\n");
    afficher_tableau(tab_selection, N);

    // Tri par insertion
    int tab_insertion[N];
    for (int i = 0; i < N; i++) tab_insertion[i] = tab[i];
    tri_insertion(tab_insertion, N);
    printf("\nTableau trié par insertion:\n");
    afficher_tableau(tab_insertion, N);

    return 0;
}