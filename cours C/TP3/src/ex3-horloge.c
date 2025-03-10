#include <stdio.h>

// Fonction de conversion du temps en secondes
int convertirEnSecondes(int heures, int minutes, int secondes) {
    return (heures * 3600) + (minutes * 60) + secondes;
}

int main() {
    int h, m, s, totalSecondes;

    // Demander à l'utilisateur d'entrer le temps
    printf("Entrez les heures : ");
    scanf("%d", &h);
    printf("Entrez les minutes : ");
    scanf("%d", &m);
    printf("Entrez les secondes : ");
    scanf("%d", &s);

    // Vérification des valeurs (optionnel)
    if (h < 0 || m < 0 || m >= 60 || s < 0 || s >= 60) {
        printf("Erreur : Valeurs incorrectes.\n");
        return 1; // Quitter avec un code d'erreur
    }

    // Conversion en secondes
    totalSecondes = convertirEnSecondes(h, m, s);

    // Affichage du résultat
    printf("Le temps total en secondes est : %d secondes\n", totalSecondes);

    return 0;
}
