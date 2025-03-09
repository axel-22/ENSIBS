#include <stdio.h>

int demander_nombre(char lettre) {
    int nombre;
    int input;

    do {
        printf("Entrez un nombre entier %c  positif:\n ", lettre);
        input = scanf("%d", &nombre);
        // Vérifier si scanf a bien lu un entier
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
        // Vérifier si le nombre est dans la plage [1,20]
        if (nombre <= 0) {
            printf("Erreur: le nombre doit être supérieur à 0\n");
        }
    } while (input != 1 || nombre <=0 );

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