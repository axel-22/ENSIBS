/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 11 - Calcul de la puissance d'un nombre
 */
#include <stdio.h>
// Fonction pour demander un nombre entier positif à l'utilisateur et le retourner
int demander_nombre(char lettre) {
    int nombre;
    int input;
    char term;

    do {
        printf("Entrez un nombre entier %c  positif:\n ", lettre);
        input = scanf("%d%c", &nombre, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2  || term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
        if (nombre <= 0) {
            printf("Erreur: le nombre doit être supérieur à 0\n");
        }
    } while (input != 2 || nombre <=0 || term != '\n');

    return nombre;
}

int main(){
    int n = demander_nombre('n');
    int x = demander_nombre('x');
    long resultat = 1;
    for (int i = 0; i < x; i++) {
        resultat = resultat * n;
    }
    printf("le résultat de %d^%d = %ld\n",n,x,resultat);
}