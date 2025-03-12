/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 5 - Opération de division entière et flottante
 */
#include <stdio.h>
// Fonction main qui affiche le résultat de plusieurs divisions
int main() {
    int entier; // Déclaration d'une variable entier
    float flottant; // Déclaration d'une variable flottant

    entier = 10 / 3; // Division de 10 par 3 en entier dans une variable entier
    printf("10 / 3 en entier : %d\n", entier);

    flottant = 10 / 3; // Division de 10 par 3 en entier dans une variable flottant
    printf("10/3 en float : %f\n", flottant);

    flottant = 10.0 / 3; // Division de 10.0 par 3 en entier dans une variable flottant
    printf("10.0 / 3 en float : %f\n", flottant);

    flottant = 10.0 / 3.0; // Division de 10.0 par 3.0 en entier dans une variable flottant
    printf("10.0 / 3.0 en float : %f\n", flottant);

    flottant = (float) 10 / 3; // Division de 10 par 3 en entier dans une variable flottant avec un cast
    printf("(float) 10 / 3 : %f\n", flottant);

    flottant = ((float) 10) / 3; // Division de 10 par 3 en entier dans une variable flottant avec un cast
    printf("((float) 10) / 3 : %f\n", flottant);

    flottant = ((float) 10) / 3; // Division de 10 par 3 en entier dans une variable flottant avec un cast
    printf("((float) 10) / 3 (1 chiffre après virgule) : %.1f\n", flottant);
    printf("((float) 10) / 3 (5 chiffres après virgule) : %.5f\n", flottant);

    // Affiche des informations sur les divisions
    printf("Si les deux éléments divisés sont des entiers, le reste de la division est ignoré");
    printf("\n10.0 est un float, donc 3 est converti en float avant la division.");
    printf("\n(float) 10 transforme 10 en 10.0, donc la division est flottante.");

    return 0;
}


