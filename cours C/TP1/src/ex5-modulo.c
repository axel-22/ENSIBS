
/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 5 - Opération de modulo
 */
#include <stdio.h>
#include <math.h>  // Inclure la librairie math.h pour utiliser la fonction fmod()

// Fonction main qui affiche le résultat de plusieurs modulo
int main() {

    int x1 = 5 % 2;  // Modulo entier sans fmod()
    double x2 = fmod(5.0, 2.0);  // Modulo flottant avec fmod()

    // Affiche les résultats des modulo
    printf("La variable entière X = %d\n", x1);
    printf("5.0%%2 : calcul impossible sans la lib math.h et la fonction fmod()\n");
    printf("La variable flottante X (avec fmod()) = %.2f\n", x2);

    return 0;
}