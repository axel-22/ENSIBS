#include <stdio.h>

int main() {

    int a = 5, b = 6;

    printf("ET bit à bit: 5 & 6 = %d\n", a & b);
    printf("le résultat vaut 4 car : 5  = 0b0101 et 6 = 0b0110 donc le resultat vaux 0b0100 donc 4 en base 10\n"); 
    printf("\n"); 
    printf("ET logique: 5 && 6 = %d\n", a && b);
    printf("le résultat vaut 1 car les deux variables a et b sont définies");
    printf("\n");
    printf("OU bit à bit: 5 | 6 = %d\n", a | b);
    printf("le résultat vaut 7 car : 5  = 0b0101 et 6 = 0b0110 donc le resultat vaux 0b0111 donc 7 en base 10\n"); 
    printf("\n");
    printf("OU logique: 5 || 6 = %d\n", a || b);
    printf("le résultat vaut 1 car les deux variables a et b sont définies");
    printf("\n");
    printf("XOR bit à bit: 5 ^ 6 = %d\n", a ^ b); 
    printf("le résultat vaut 3 car : 5  = 0b0101 et 6 = 0b0110 donc le resultat vaux 0b0011 donc 3 en base 10\n");
    printf("\n");
    printf("XOR logique 5 ^^ 6 = ? impossible, cela provoque une erreur car l'opération ^^ n'est pas définie en c\n");
    printf("\n");
    printf("Complément à 1, négation bit à bit: ~5 = %d\n", ~a);
    printf("le résultat vaut -6 car : 5  = 0b0000000 00000101  ~5 =  0b11111111 11111010 donc -6 le complément à 2\n");
    printf("\n");
    printf("Négation logique !5 = %d\n", !a);
    printf("le résultat vaut 0 car 5 et vrai donc !5 est faux");


    return 0;
}
