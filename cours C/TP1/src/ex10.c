/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 10 - Calcul du PGCD de deux nombres
 */
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
    int input;
    char term;
    
    // Demande des entrées à l'utilisateur
    do {
        printf("Entrez le premier nombre: ");
        input = scanf("%d%c", &a, &term);

        if (input != 2 || term != '\n') {
            printf("Erreur : veuillez entrer un seul entier.\n");
            while (getchar() != '\n');  // Vider le buffer
        } else {
            printf("Vous avez entré : %d\n", a);
        }
    } while (input != 2 || term != '\n');
    
    do {
        printf("Entrez le second nombre: ");
        input = scanf("%d", &b);
        // Vérifier si scanf a bien lu un entier
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
        if (b <= 0) {
            printf("Erreur: le nombre doit être supérieur à 0\n");
        }
    } while (input != 1 || b <=0 );

    // Calcul du PGCD et affichage du résultat
    printf("Le PGCD de %d et %d est : %d\n", a, b, pgcd(a, b));

    return 0;
}
