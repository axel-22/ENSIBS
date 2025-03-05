#include <stdio.h>

int main() {
    char operateur;
    float a, b;
    char input;
    float nb;

    do{
        printf("\nEntrez une operation (+, -, *, /) ou 's' pour sortir : ");
        input = scanf(" %c", &operateur);
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            while (getchar() != '\n');
            continue;
        }
        if (operateur != '+' && operateur != '-' && operateur != '*' && operateur != '/' && operateur != 's'){
            printf("Erreur: Veuillez entrer un caractère parmis (+, -, *, /,s) !\n");
            continue;
        }
        if (operateur == 's') {
            printf("Programme terminé.\n");
            break;
        }
        
        do{
            printf("Entrez deux nombres : ");
            nb = scanf("%f %f", &a, &b);
            if (nb != 2) {
                printf("Erreur: Veuillez entrer deux nombres flottants valides !\n");
                while (getchar() != '\n');
                continue;
            }
        }while (nb != 2);
        
        if(operateur == '+'){
            printf("Résultat : %.2f\n", a + b);
        }else if(operateur == '-'){
            printf("Résultat : %.2f\n", a - b);
        }else if(operateur == '*'){
            printf("Résultat : %.2f\n", a * b);
        }else if(operateur == '/'){
            printf("Résultat : %.2f\n", a / b);
        }

    } while (operateur != 's');

    return 0;
}
