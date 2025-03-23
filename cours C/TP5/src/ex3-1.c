/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP5 - Exercice 3 - Echange de valeurs
 */
#include <stdio.h>

void echanger(int *pa, int *pb) {
    int tmp;
    tmp = *pa;  // Stocke la valeur pointée par pa
    *pa = *pb;  // Copie la valeur pointée par pb dans *pa
    *pb = tmp;  // Copie tmp dans *pb
}

int main() {
    int x, y;
    
    x = 12;
    y = 34;
    
    printf("Avant échange : x = %d ; y = %d\n", x, y);
    
    echanger(&x, &y);  // Passage par adresse
    
    printf("Après échange : x = %d ; y = %d\n", x, y);
    
    return 0;
}
