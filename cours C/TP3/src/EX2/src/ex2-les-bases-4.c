/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP3 - Exercice 2 - Hello World avec une autre librairie
 */
#include <stdio.h>
#include "fonction2.h" // import de la librairie qui contient le prototype hw

void hw(){
    printf("Hello world\n");
}

int main() {
    hw(); // appel de notre fonction
    return 0;
}
