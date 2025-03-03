#include <stdio.h>

int main() {
    int entier;
    float flottant;

    entier = 10 / 3;
    printf("10 / 3 en entier : %d\n", entier);

    flottant = 10 / 3;
    printf("10/3 en float : %f\n", flottant);

    flottant = 10.0 / 3;
    printf("10.0 / 3 en float : %f\n", flottant);

    flottant = 10.0 / 3.0;
    printf("10.0 / 3.0 en float : %f\n", flottant);

    flottant = (float) 10 / 3;
    printf("(float) 10 / 3 : %f\n", flottant);

    flottant = ((float) 10) / 3;
    printf("((float) 10) / 3 : %f\n", flottant);

    flottant = ((float) 10) / 3;
    printf("((float) 10) / 3 (1 chiffre après virgule) : %.1f\n", flottant);
    printf("((float) 10) / 3 (5 chiffres après virgule) : %.5f\n", flottant);

    printf("Si les deux éléments divisés sont des entiers, le reste de la division est ignoré");
    printf("\n10.0 est un float, donc 3 est converti en float avant la division.");
    printf("\n(float) 10 transforme 10 en 10.0, donc la division est flottante.");

    return 0;
}


