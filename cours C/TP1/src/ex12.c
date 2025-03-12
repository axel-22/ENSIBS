/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 12 - Compter le nombre de voyelles dans un texte
 */
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 1000  // Taille maximale du texte

// Fonction pour vérifier si un caractère est une voyelle
int est_voyelle(char c) {
    int ret = 0;
    char voyelles[] = "aeiouyAEIOUY";
    for (int i = 0; voyelles[i] != '\0'; i++) {
        if (c == voyelles[i]) {
            ret = 1;
        }
    }
    return ret;
}

int main() {
    char texte[TAILLE_MAX];
    int compteur = 0;

    printf("Entrez un texte terminé par '#' : ");
    scanf("%[^\n]", texte);  // Lire jusqu'à un saut de ligne

    int longueur = strlen(texte);

    // Vérifier si le texte est vide ou ne se termine pas par '#'
    if (longueur == 0 || texte[longueur - 1] != '#') {
        printf("Erreur : le texte doit se terminer par le caractère '#'.\n");
        return 1;  // Sortie avec erreur
    }

    // Parcours et comptage des voyelles (sans compter le '#')
    for (int i = 0; i < longueur - 1; i++) {
        if (est_voyelle(texte[i])) {
            compteur++;
        }
    }

    printf("Nombre de voyelles dans le texte : %d\n", compteur);

    return 0;
}
