/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP3 - Exercice 3 - Convertie en heure minutes seconde
 */
#include <stdio.h>

// Fonction de conversion du temps en secondes
int convertirEnSecondes(int heures, int minutes, int secondes) {
    return (heures * 3600) + (minutes * 60) + secondes;
}

int main() {
    int h, m, s, totalSecondes;
    int input;
    char term;
    // Demander à l'utilisateur d'entrer le temps
    do {
        printf("Entrez les heures : ");
        input = scanf("%d%c", &h, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || h < 0 || term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || h < 0 || term != '\n');
      
    do {
        printf("Entrez les minutes : ");
        input = scanf("%d%c", &m, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2  || m < 0 || m > 60|| term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || m < 0 || m > 60 || term != '\n');

    do {
        printf("Entrez les secondes : ");
        input = scanf("%d%c", &s, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2  || s < 0 || s > 60|| term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || s < 0 || s > 60 || term != '\n');

    // Conversion en secondes
    totalSecondes = convertirEnSecondes(h, m, s);

    // Affichage du résultat
    printf("Le temps total en secondes est : %d secondes\n", totalSecondes);

    return 0;
}
