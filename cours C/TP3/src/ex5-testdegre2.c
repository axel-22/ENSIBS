#include <stdio.h>
#include "degre.h"

// Fonction pour lire le choix utilisateur avec validation
int lireChoix() {
    int choix;
    printf("\nMenu de conversion :\n");
    printf("1 - Celsius → Kelvin\n");
    printf("2 - Celsius → Fahrenheit\n");
    printf("3 - Kelvin → Celsius\n");
    printf("4 - Fahrenheit → Celsius\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");

    // Vérification de l'entrée utilisateur
    if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n'); // Vide le buffer en cas d'erreur
        printf("Entrée invalide ! Veuillez entrer un nombre.\n");
        return -1; // Code d'erreur
    }

    return choix;
}

// Exécuter la conversion en fonction du choix
void executerChoix(int choix) {
    float valeur, resultat;

    switch (choix) {
        case 1:
            printf("Entrez la température en Celsius : ");
            if (scanf("%f", &valeur) != 1) {
                while (getchar() != '\n');
                printf("Entrée invalide !\n");
                return;
            }
            resultat = CelsiusAKelvin(valeur);
            printf("%.2f°C = %.2f K\n", valeur, resultat);
            break;

        case 2:
            printf("Entrez la température en Celsius : ");
            if (scanf("%f", &valeur) != 1) {
                while (getchar() != '\n');
                printf("Entrée invalide !\n");
                return;
            }
            resultat = CelsiusAFahrenheit(valeur);
            printf("%.2f°C = %.2f°F\n", valeur, resultat);
            break;

        case 3:
            printf("Entrez la température en Kelvin : ");
            if (scanf("%f", &valeur) != 1) {
                while (getchar() != '\n');
                printf("Entrée invalide !\n");
                return;
            }
            resultat = KelvinACelsius(valeur);
            if (resultat != -1)
                printf("%.2f K = %.2f°C\n", valeur, resultat);
            break;

        case 4:
            printf("Entrez la température en Fahrenheit : ");
            if (scanf("%f", &valeur) != 1) {
                while (getchar() != '\n');
                printf("Entrée invalide !\n");
                return;
            }
            resultat = FahrenheitACelsius(valeur);
            printf("%.2f°F = %.2f°C\n", valeur, resultat);
            break;

        case 0:
            printf("Programme terminé.\n");
            break;

        default:
            printf("Choix invalide !\n");
    }
}

int main() {
    int choix;
    do {
        choix = lireChoix();
        if (choix != -1)
            executerChoix(choix);
    } while (choix != 0);

    return 0;
}
