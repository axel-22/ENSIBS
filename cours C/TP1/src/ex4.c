/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 4 - ordre des opérations
 */
#include <stdio.h>
// Fonction intitulé calcul_x sans retour qui affiche le résultat de plusieurs calculs
void calcul_x() {
    int X;
    
    X = -3 + 4 * 5 - 6; // Calcul de x sans parenthèses
    printf("X = -3 + 4 * 5 - 6 = %d\n", X);

    X = (-3 + 4) * 5 - 6; // Calcul de x avec parenthèses
    printf("X = (-3 + 4) * 5 - 6 = %d\n", X);

    X = -3 + (4 * 5) - 6; // Calcul de x avec d'autres parenthèses
    printf("X = -3 + (4 * 5) - 6 = %d\n", X);

    X = -3 + 4 * (5 - 6); // Calcul de x avec d'autres parenthèses
    printf("X = -3 + 4 * (5 - 6) = %d\n", X);
}
// Fonction main qui appelle la fonction calcul_x
int main() {
    calcul_x(); // Appel de la fonction calcul_x
    return 0;
}