/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 8 - Affiche le résultat d'une opération sélectionnée 
 * par l'utilisateur sur deux nombres a et b en utilisant des if
 */
#include <stdio.h>
// calculatrice simple
int main() {
    char operateur;
    float a, b;
    char input;
    char term;
    while(1){ // boucle principale infinie tant que l'utilisateur ne rentre pas 's'
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

        if (operateur == 's') {
            printf("Programme terminé.\n");
            break;

        }else{

            do {
                printf("Entrez deux nombres : ");
                input = scanf("%f %f%c", &a, &b, &term);
        
                if (input != 3 || term != '\n') {
                    printf("Erreur : veuillez entrer exactement deux nombres valides.\n");
                    while (getchar() != '\n'); // Vider le buffer pour éviter une boucle infinie
                }
            } while (input != 3 || term != '\n'); // boucle tant que l'utilisateur ne rentre pas deux nombres
            
            if(operateur == '+'){
                printf("Résultat : %.2f\n", a + b);
            }else if(operateur == '-'){
                printf("Résultat : %.2f\n", a - b);
            }else if(operateur == '*'){
                printf("Résultat : %.2f\n", a * b);
            }else if(operateur == '/'){
                printf("Résultat : %.2f\n", a / b);
            }

        }
    }
    return 0;
}
