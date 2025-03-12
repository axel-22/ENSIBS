/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 9 - Affiche la somme des entiers de 1 à n en utilisant des boucles for et while
 */
#include <stdio.h>
// Fonction qui demande un nombre entier à l'utilisateur et le retourne
int demander_nombre() {
    int nombre;
    int input;

    do {
        printf("Entrez un nombre entier > 0 : ");
        input = scanf("%d", &nombre);
        // Vérifier si scanf a bien lu un entier
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
        if (nombre <= 0) {
            printf("Erreur: le nombre doit être supérieur à 0\n");
        }
    } while (input != 1 || nombre <=0 );

    return nombre;
}
// Fonction qui calcule la somme des entiers de 1 à n en utilisant une boucle for à indice incrémenté
void boucle_for_i(int n){
    int somme;
    somme = 0;
    for(int i = 1; i <= n ; i++){
        somme = somme + i;
    }
    
    printf("Une boucle for à indice incrémenté entre 0 et %d\n",n);
    printf("somme = %d\n", somme);
}
// Fonction qui calcule la somme des entiers de 1 à n en utilisant une boucle for à indice décrémenté
void boucle_for_d(int n){
    int somme;
    somme = 0;
    for(int i = n; i > 0; i--){
        somme = somme + i;
    }
    
    printf("Une boucle for à indice décrémenté entre 0 et %d\n",n);
    printf("somme = %d\n", somme);
}
// Fonction qui calcule la somme des entiers de 1 à n en utilisant une boucle while à indice incrémenté
void boucle_while_i(int n){
    int somme;
    somme = 0;
    int i = 1;
    while(i <= n){
        somme = somme + i;
        i++;
    }
    
    printf("Une boucle while à indice incrémenté entre 0 et %d\n",n);
    printf("somme = %d\n", somme);
}
// Fonction qui calcule la somme des entiers de 1 à n en utilisant une boucle while à indice décrémenté
void boucle_while_d(int n){
    int somme;
    somme = 0;
    int i = n;
    while(i > 0){
        somme = somme + i;
        i--;
    }
    
    printf("Une boucle while à indice décrémenté entre 0 et %d\n",n);
    printf("somme = %d\n", somme);
}

int main() {
    int n;
    n = demander_nombre();
    printf("n = %d\n", n);
    // Appel des fonctions de calcul de somme
    boucle_for_i(n);
    boucle_for_d(n);
    boucle_while_i(n);
    boucle_while_d(n);

    return 0;
}
