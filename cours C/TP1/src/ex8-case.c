#include <stdio.h>

int main() {
    char operateur;
    float a, b;

    while (1) {
        printf("\nEntrez une operation (+, -, *, /) ou 's' pour sortir : ");
        scanf(" %c", &operateur);

        if (operateur == 's') {
            printf("Programme terminé.\n");
            break;
        }

        switch (operateur) {
            case '+':
            case '-':
            case '*':
            case '/':
                printf("Entrez deux nombres : ");
                scanf("%f %f", &a, &b);

                switch (operateur) {
                    case '+':
                        printf("Résultat : %.2f\n", a + b);
                        break;
                    case '-':
                        printf("Résultat : %.2f\n", a - b);
                        break;
                    case '*':
                        printf("Résultat : %.2f\n", a * b);
                        break;
                    case '/':
                        if (b == 0) {
                            printf("Erreur : division par zéro impossible.\n");
                        } else {
                            printf("Résultat : %.2f\n", a / b);
                        }
                        break;
                }
                break;

            default:
                printf("Erreur : opération non reconnue.\n");
        }
    }
    return 0;
}
