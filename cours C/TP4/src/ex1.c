#include <stdio.h>

// Définition de la structure avec typedef
typedef struct {
    char nom[50];
    int age;
} Personne;

int main(void) {
    // Déclaration d'une variable de type Personne
    Personne p1;

    // Saisie des données
    printf("Entrez le nom : ");
    scanf("%49s", p1.nom); // Limite à 49 caractères pour éviter le dépassement
    printf("Entrez l'âge : ");
    scanf("%d", &p1.age);

    // Affichage des données
    printf("Nom : %s\n", p1.nom);
    printf("Âge : %d\n", p1.age);

    return 0;
}
