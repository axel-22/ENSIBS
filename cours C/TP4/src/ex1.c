/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP4 - Exercice 1 - Apprentisage des struct
 */
#include <stdio.h>
#include <string.h>

// Définition de la structure avec typedef
typedef struct {
    char nom[50];
    int age;
} Personne;


int is_valid_name(const char *nom) {
    int ret = 1;
    // Liste des caractères valides
    const char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúàèìòùâêîôûäëïöüãõçÇàèéù'-";
    
    while (*nom) {
        if (!strchr(valid_chars, *nom)) {
            ret = 0;  // Caractère invalide trouvé
        }
        nom++;
    }
    return ret;  // Tous les caractères sont valides
}
int main(void) {
    // Déclaration d'une variable de type Personne
    Personne p1;

    // Saisie des données
    int input;
    char term;
    do {
        printf("Entrez le nom : ");
        input = scanf("%49s%c", p1.nom, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || !is_valid_name(p1.nom) || term != '\n') {
            printf("Erreur: Veuillez entrer un nom valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || !is_valid_name(p1.nom) || term != '\n');

    do {
        printf("Entrez l'âge : ");
        input = scanf("%d%c", &p1.age, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || p1.age <= 0 || p1.age > 130 || term != '\n') {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || p1.age <= 0 || p1.age > 130 || term != '\n');

    // Affichage des données
    printf("Nom : %s\n", p1.nom);
    printf("Âge : %d\n", p1.age);

    return 0;
}
