#include <stdio.h>

// Fonction pour calculer le PGCD de deux nombres
int pgcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;  // Calcul du reste de la division
        a = temp;   // Mise à jour de a avec b
    }
    return a;  // a contient le PGCD
}

int main() {
    int a, b;

    // Demande des entrées à l'utilisateur
    printf("Entrez le premier nombre: ");
    scanf("%d", &a);
    printf("Entrez le second nombre: ");
    scanf("%d", &b);

    // Calcul du PGCD et affichage du résultat
    printf("Le PGCD de %d et %d est : %d\n", a, b, pgcd(a, b));

    return 0;
}
