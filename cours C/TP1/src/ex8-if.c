#include <stdio.h>

int main() {
    char operateur;
    float a, b;
    char input;
    float nb;
    char term;

    do {
        printf("\nEntrez une operation (+, -, *, /) ou 's' pour sortir : ");
        input = scanf(" %c%c", &operateur, &term);  // Lire un caractère et le caractère suivant

        if (input != 2 || term != '\n') {
            printf("Erreur : veuillez entrer un seul caractère.\n");
            while (getchar() != '\n');  // Vider le buffer pour éviter une boucle infinie
        } else if (!(operateur == '+' || operateur == '-' || operateur == '*' || operateur == '/' || operateur == 's')) {
            printf("Erreur : caractère non valide. Utilisez +, -, *, ou  's' pour sortir /.\n");
            input = 0;  // Forcer la boucle à continuer
        }

    } while (input != 2 || term != '\n'); // boucle tant que l'utilisateur ne rentre pas un seul caractère
        
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
