
#include <stdio.h>
#include <math.h>  

int main() {

    int x1 = 5 % 2;  // Modulo entier
    double x2 = fmod(5.0, 2.0);  // Modulo flottant

    printf("La variable entière X = %d\n", x1);
    printf("5.0%%2 : calcul impossible sans la lib math.h et la fonction fmod()\n");
    printf("La variable flottante X (avec fmod()) = %.2f\n", x2);

    return 0;
}