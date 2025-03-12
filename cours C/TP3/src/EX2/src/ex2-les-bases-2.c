/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP3 - Exercice 2 - Hello World avec prototype 
 */
#include <stdio.h>

void hw(); // Le prototype ici

int main() {
    hw(); // OK, le compilateur connaît maintenant la fonction
    return 0;
}
// réécriture du prototype
void hw() {
    printf("Hello world\n");
}
