/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP2 - Exercice 2 - Tri par recherche du minima successifs
 */
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


int main() {
    int tab[N];
    srand(time(NULL));

    // Remplissage aléatoire du tableau
    for (int i = 0; i < N; i++) {
        tab[i] = rand() % (MAX_VALUE + 1);
    }

    printf("Tableau original:\n");
    afficher_tableau(tab, N);

    // Tri par sélection
    int tab_selection[N];
    for (int i = 0; i < N; i++) tab_selection[i] = tab[i];
    tri_selection(tab_selection, N);
    printf("\nTableau trié par sélection:\n");
    afficher_tableau(tab_selection, N);


    return 0;
}