/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP4 - Exercice 2 - Apprentisage des struct, manipulation de personnes
 */
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

// Vérifier si une année est bissextile
int est_bissextile(int annee) {
    int ret = 0;
    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        ret = 1;
    }
    return ret;
}

// Vérifier si une date est valide et dans la plage autorisée
int est_date_valide(int jour, int mois, int annee) {
    int ret = 1;
    //vérification de la plage de l'année
    if (annee < 1900 || annee > 2025){
        ret = 0;
    }
    // Vérification de la plage du mois
    if (mois < 1 || mois > 12) {
        ret = 0;
    }
    // jours max dans chaque mois
    int jours_dans_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
    // Vérification du jour en fonction du mois
    if (mois == 2 && est_bissextile(annee)) {
        if (jour < 1 || jour > 29){
            ret = 0;
        }
    } else {
        if (jour < 1 || jour > jours_dans_mois[mois - 1]){
            ret = 0;
        }
    }

    // Vérification de la limite maximale : 30/03/2025
    if (annee == 2025) {
        //Vérification en fonction de la date de rendu du TP
        if (mois > 3 || (mois == 3 && jour > 30)){
            ret = 0;
        }
    }

    return ret;
}
// Fonction pour définir une personne
void definir_personne() {
    if (nombre_personnes >= 20) {
        printf("Le tableau est plein. Impossible d'ajouter plus de personnes.\n");
        return;
    }

    struct PERSONNE p;
    int input;
    char term;
    do {
        printf("Entrez le nom de la personne : ");
        input = scanf("%49s%c", p.nom, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || !is_valid_name(p.nom) || term != '\n') {
            printf("Erreur: Veuillez entrer un nom valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || !is_valid_name(p.nom) || term != '\n');
    do {
        printf("Entrez le prénom de la personne : ");
        input = scanf("%49s%c", p.prenom, &term);
        // Vérifier si scanf a bien lu un entier
        if (input != 2 || !is_valid_name(p.prenom) || term != '\n') {
            printf("Erreur: Veuillez entrer un nom valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
    } while (input != 2 || !is_valid_name(p.prenom) || term != '\n');
    
    // Demander et valider la date de naissance
    do {
        printf("Entrez le jour de naissance : ");
        scanf("%d", &p.date_naissance.jour);
        printf("Entrez le mois de naissance : ");
        scanf("%d", &p.date_naissance.mois);
        printf("Entrez l'année de naissance : ");
        scanf("%d", &p.date_naissance.annee);

        if (!est_date_valide(p.date_naissance.jour, p.date_naissance.mois, p.date_naissance.annee)) {
            printf("Erreur: Veuillez entrer une date valide entre 01/01/1900 et 30/03/2025.\n");
            while (getchar() != '\n');  // Nettoyer le buffer
            continue;
        } else {
            break;  // Date valide, sortir de la boucle
        }
    } while (1);

    printf("La personne a été ajoutée.\n");
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
    int input;
    char term;
    printf("Entrez le nom de la personne à modifier : ");
    scanf("%s", nom);

    int trouve = 0;
    for (int i = 0; i < nombre_personnes; i++) {
        if (strcmp(personnes[i].nom, nom) == 0) {
            printf("Personne trouvée :\n");
            afficher_personne(personnes[i]);
            printf("Modifiez les données de la personne (nouveau prénom, nouvelle date de naissance) :\n");
            do {
                printf("Entrez le prénom de la personne : ");
                input = scanf("%49s%c", personnes[i].prenom, &term);
                // Vérifier si scanf a bien lu un entier
                if (input != 2 || !is_valid_name(personnes[i].prenom) || term != '\n') {
                    printf("Erreur: Veuillez entrer un nom valide !\n");
                    // Nettoyer le buffer en vidant les entrées invalides
                    while (getchar() != '\n');
                    continue;  // Recommencer la boucle
                }
            } while (input != 2 || !is_valid_name(personnes[i].prenom) || term != '\n');
            
            // Demander et valider la date de naissance
            do {
                printf("Entrez le jour de naissance : ");
                scanf("%d", &personnes[i].date_naissance.jour);
                printf("Entrez le mois de naissance : ");
                scanf("%d", &personnes[i].date_naissance.mois);
                printf("Entrez l'année de naissance : ");
                scanf("%d", &personnes[i].date_naissance.annee);
        
                if (!est_date_valide(personnes[i].date_naissance.jour, personnes[i].date_naissance.mois, personnes[i].date_naissance.annee)) {
                    printf("Erreur: Veuillez entrer une date valide entre 01/01/1900 et 30/03/2025.\n");
                    while (getchar() != '\n');  // Nettoyer le buffer
                    continue;
                } else {
                    break;  // Date valide, sortir de la boucle
                }
            } while (1);
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
    int input;
    char term;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Définir une personne\n");
        printf("2. Afficher toutes les personnes\n");
        printf("3. Trier les personnes par date de naissance\n");
        printf("4. Modifier une personne par nom\n");
        printf("5. Supprimer une personne\n");
        printf("6. Quitter\n");
        do {
            printf("Entrez votre choix : ");
            input = scanf("%d%c", &choix, &term);
            // Vérifier si scanf a bien lu un entier
            if (input != 2 || choix < 1 || choix > 6 || term != '\n') {
                printf("Erreur: Veuillez entrer un numéro valide !\n");
                // Nettoyer le buffer en vidant les entrées invalides
                while (getchar() != '\n');
                continue;  // Recommencer la boucle
            }
        } while (input != 2 || choix < 1 || choix > 6 || term != '\n');
       

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
