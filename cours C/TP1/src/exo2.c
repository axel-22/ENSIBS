#include <stdio.h>

void calcul_x() {
    int X;
    
    X = -3 + 4 * 5 - 6;
    printf("X = -3 + 4 * 5 - 6 = %d\n", X);

    X = (-3 + 4) * 5 - 6;
    printf("X = (-3 + 4) * 5 - 6 = %d\n", X);

    X = -3 + (4 * 5) - 6;
    printf("X = -3 + (4 * 5) - 6 = %d\n", X);

    X = -3 + 4 * (5 - 6);
    printf("X = -3 + 4 * (5 - 6) = %d\n", X);
}

int main() {
    calcul_x();
    return 0;
}