#include <stdio.h>
#include <string.h>

// Définition de la structure DATE
struct DATE {
    int jour;
    int mois;
    int annee;
};

// Définition de la structure PERSONNE
struct PERSONNE {
    char nom[20];
    char prenom[20];
    struct DATE date_naissance;
};

// Déclaration du tableau de personnes (dimension maximale de 20)
struct PERSONNE personnes[20];
int nombre_personnes = 0;  // Variable pour suivre le nombre de personnes enregistrées

// Fonction pour définir une personne
void definir_personne() {
    if (nombre_personnes >= 20) {
        printf("Le tableau est plein. Impossible d'ajouter plus de personnes.\n");
        return;
    }

    struct PERSONNE p;
    printf("Entrez le nom de la personne : ");
    scanf("%s", p.nom);
    printf("Entrez le prénom de la personne : ");
    scanf("%s", p.prenom);
    printf("Entrez le jour de naissance : ");
    scanf("%d", &p.date_naissance.jour);
    printf("Entrez le mois de naissance : ");
    scanf("%d", &p.date_naissance.mois);
    printf("Entrez l'année de naissance : ");
    scanf("%d", &p.date_naissance.annee);

    personnes[nombre_personnes] = p;
    nombre_personnes++;
}

// Fonction pour afficher les données d'une personne
void afficher_personne(struct PERSONNE p) {
    printf("Nom : %s\n", p.nom);
    printf("Prénom : %s\n", p.prenom);
    printf("Date de naissance : %02d/%02d/%d\n", p.date_naissance.jour, p.date_naissance.mois, p.date_naissance.annee);
}

// Fonction pour afficher toutes les personnes
void afficher_toutes_les_personnes() {
    if (nombre_personnes == 0) {
        printf("Aucune personne enregistrée.\n");
        return;
    }

    for (int i = 0; i < nombre_personnes; i++) {
        afficher_personne(personnes[i]);
    }
}

// Fonction pour classer les personnes par date de naissance
int comparer_dates(struct DATE d1, struct DATE d2) {
    if (d1.annee != d2.annee)
        return d1.annee - d2.annee;
    if (d1.mois != d2.mois)
        return d1.mois - d2.mois;
    return d1.jour - d2.jour;
}

void trier_par_date_naissance() {
    for (int i = 0; i < nombre_personnes - 1; i++) {
        for (int j = i + 1; j < nombre_personnes; j++) {
            if (comparer_dates(personnes[i].date_naissance, personnes[j].date_naissance) > 0) {
                struct PERSONNE temp = personnes[i];
                personnes[i] = personnes[j];
                personnes[j] = temp;
            }
        }
    }
    printf("Les personnes ont été triées par date de naissance.\n");
}

// Fonction pour retrouver, modifier et afficher les données d'une personne à partir de son nom
void modifier_personne_par_nom() {
    char nom[20];
    printf("Entrez le nom de la personne à modifier : ");
    scanf("%s", nom);

    int trouve = 0;
    for (int i = 0; i < nombre_personnes; i++) {
        if (strcmp(personnes[i].nom, nom) == 0) {
            printf("Personne trouvée :\n");
            afficher_personne(personnes[i]);
            printf("Modifiez les données de la personne (nouveau prénom, nouvelle date de naissance) :\n");
            printf("Entrez le nouveau prénom : ");
            scanf("%s", personnes[i].prenom);
            printf("Entrez le nouveau jour de naissance : ");
            scanf("%d", &personnes[i].date_naissance.jour);
            printf("Entrez le nouveau mois de naissance : ");
            scanf("%d", &personnes[i].date_naissance.mois);
            printf("Entrez la nouvelle année de naissance : ");
            scanf("%d", &personnes[i].date_naissance.annee);
            printf("Les données ont été modifiées.\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Personne non trouvée.\n");
    }
}

// Fonction pour supprimer un enregistrement
void supprimer_personne() {
    char nom[20];
    printf("Entrez le nom de la personne à supprimer : ");
    scanf("%s", nom);

    int trouve = 0;
    for (int i = 0; i < nombre_personnes; i++) {
        if (strcmp(personnes[i].nom, nom) == 0) {
            for (int j = i; j < nombre_personnes - 1; j++) {
                personnes[j] = personnes[j + 1];  // Décalage des éléments
            }
            nombre_personnes--;
            printf("La personne a été supprimée.\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Personne non trouvée.\n");
    }
}

// Fonction pour afficher le menu et choisir l'option
void menu() {
    int choix;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Définir une personne\n");
        printf("2. Afficher toutes les personnes\n");
        printf("3. Trier les personnes par date de naissance\n");
        printf("4. Modifier une personne par nom\n");
        printf("5. Supprimer une personne\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                definir_personne();
                break;
            case 2:
                afficher_toutes_les_personnes();
                break;
            case 3:
                trier_par_date_naissance();
                break;
            case 4:
                modifier_personne_par_nom();
                break;
            case 5:
                supprimer_personne();
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Essayez de nouveau.\n");
        }
    } while (choix != 6);
}

int main() {
    menu();
    return 0;
}
