/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP6 - Exercice 1 - Controle d'accès
 */
#include <stdio.h>
#include <string.h>
#include <time.h> // Pour la gestion du temps
#include <stdlib.h> // Pour malloc

// Structure de la personne
struct PERSONNE {
    char nom[20];
    char prenom[20];
    int badge;
    int code;
    time_t dernier_passage;
    struct PERSONNE* prev;
    struct PERSONNE* next;
};

// Vérifier si le nom est valide
int is_valid_name(const char *nom) {
    const char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúàèìòùâêîôûäëïöüãõçÇàèéù'-";
    while (*nom) {
        if (!strchr(valid_chars, *nom)) {
            return 0;
        }
        nom++;
    }
    return 1;
}

// Ajouter une personne à la liste
struct PERSONNE* ajouter_personne(struct PERSONNE* head) {
    struct PERSONNE* p = malloc(sizeof(struct PERSONNE));
    if (!p) {
        printf("Erreur d'allocation mémoire.\n");
        return head;
    }

    int input;
    char term;

    do {
        printf("Entrez le nom de la personne : ");
        input = scanf("%19s%c", p->nom, &term);
        if (input != 2 || !is_valid_name(p->nom) || term != '\n') {
            printf("Erreur: Veuillez entrer un nom valide !\n");
            while (getchar() != '\n');
        }
    } while (input != 2 || !is_valid_name(p->nom) || term != '\n');

    do {
        printf("Entrez le prénom de la personne : ");
        input = scanf("%19s%c", p->prenom, &term);
        if (input != 2 || !is_valid_name(p->prenom) || term != '\n') {
            printf("Erreur: Veuillez entrer un prénom valide !\n");
            while (getchar() != '\n');
        }
    } while (input != 2 || !is_valid_name(p->prenom) || term != '\n');

    char badge_str[5];
    do {
        printf("Entrez un identifiant de badge (4 chiffres) : ");
        input = scanf("%4d%c", &p->badge, &term);
        sprintf(badge_str, "%d", p->badge);
        if (input != 2 || strlen(badge_str) != 4 || term != '\n') {
            printf("Erreur: Veuillez entrer un badge valide de 4 chiffres !\n");
            while (getchar() != '\n');
        }
    } while (input != 2 || strlen(badge_str) != 4 || term != '\n');

    do {
        printf("Entrez le code secret (maximum 6 chiffres) : ");
        input = scanf("%6d%c", &p->code, &term);
        if (input != 2 || term != '\n') {
            printf("Erreur: Veuillez entrer un code valide !\n");
            while (getchar() != '\n');
        }
    } while (input != 2 || term != '\n');

    p->dernier_passage = time(NULL);
    p->prev = NULL;
    p->next = head;
    if (head) head->prev = p;
    
    printf("La personne a été ajoutée.\n");
    return p;
}

// Afficher la liste
void afficher_liste(struct PERSONNE* head) {
    struct PERSONNE* current = head;
    while (current) {
        printf("Nom: %s, Prénom: %s, Badge: %d, Dernier passage: %s",
               current->nom, current->prenom, current->badge, ctime(&current->dernier_passage));
        current = current->next;
    }
}

// Supprimer une personne en fonction de son badge
struct PERSONNE* supprimer_personne(struct PERSONNE* head, int badge) {
    struct PERSONNE* current = head;

    while (current) {
        if (current->badge == badge) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;

            // Si la personne à supprimer est le premier élément
            if (current == head) head = current->next;

            free(current);
            printf("La personne avec le badge %d a été supprimée.\n", badge);
            return head;
        }
        current = current->next;
    }

    printf("Aucune personne trouvée avec le badge %d.\n", badge);
    return head;
}

// Libérer la mémoire de la liste
void liberer_liste(struct PERSONNE* head) {
    struct PERSONNE* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Modifier le code secret d'une personne par badge
struct PERSONNE* modifier_code(struct PERSONNE* head, int badge) {
    struct PERSONNE* current = head;

    while (current) {
        if (current->badge == badge) {
            int nouveau_code;
            printf("Entrez le nouveau code secret pour la personne avec le badge %d : ", badge);
            scanf("%d", &nouveau_code);
            current->code = nouveau_code;
            printf("Le code secret a été modifié pour la personne avec le badge %d.\n", badge);
            return head;
        }
        current = current->next;
    }

    printf("Aucune personne trouvée avec le badge %d.\n", badge);
    return head;
}

// Simuler le contrôle d'accès
void controler_acces(struct PERSONNE* head) {
    int badge, code;
    struct PERSONNE* current = head;

    // Saisir le numéro de badge
    printf("Entrez le numéro de badge : ");
    scanf("%d", &badge);

    // Chercher la personne avec le badge donné
    while (current) {
        if (current->badge == badge) {
            // Si le badge correspond, demander le code secret
            printf("Entrez le code secret pour le badge %d : ", badge);
            scanf("%d", &code);

            // Vérifier le code secret
            if (current->code == code) {
                // Afficher le nom et l'heure de la visite
                printf("Accès autorisé.\n");
                printf("Nom: %s, Prénom: %s\n", current->nom, current->prenom);
                current->dernier_passage = time(NULL); // Mettre à jour l'heure de la visite
                printf("Date et heure de la visite: %s", ctime(&current->dernier_passage));
            } else {
                // Si le code est incorrect
                printf("Accès refusé : Code secret incorrect.\n");
            }
            return;
        }
        current = current->next;
    }

    // Si le badge n'existe pas
    printf("Accès refusé : Badge non reconnu.\n");
}

// Sauvegarder la liste des personnes dans un fichier
void sauvegarder_liste(struct PERSONNE* head) {
    FILE *fichier = fopen("liste_personnes.txt", "w");
    if (!fichier) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    struct PERSONNE* current = head;
    while (current) {
        fprintf(fichier, "%s %s %d %d %ld\n", 
                current->nom, current->prenom, current->badge, 
                current->code, current->dernier_passage);
        current = current->next;
    }

    fclose(fichier);
    printf("Liste des personnes sauvegardée avec succès.\n");
}

// Charger la liste des personnes depuis un fichier
struct PERSONNE* charger_liste(struct PERSONNE* head) {
    FILE *fichier = fopen("liste_personnes.txt", "r");
    if (!fichier) {
        printf("Erreur d'ouverture du fichier.\n");
        return head;
    }

    struct PERSONNE* new_person = NULL;
    while (!feof(fichier)) {
        new_person = malloc(sizeof(struct PERSONNE));
        if (fscanf(fichier, "%19s %19s %d %d %ld\n", 
                   new_person->nom, new_person->prenom, 
                   &new_person->badge, &new_person->code, 
                   &new_person->dernier_passage) == 5) {
            new_person->next = head;
            new_person->prev = NULL;
            if (head) head->prev = new_person;
            head = new_person;
        } else {
            free(new_person); // Libérer si la lecture échoue
            break;
        }
    }

    fclose(fichier);
    printf("Liste des personnes chargée avec succès.\n");
    return head;
}

int main() {
    struct PERSONNE* head = NULL;
    int choix;
    int badge;
    char term;

    do {
        printf("\nMenu:\n");
        printf("1. Afficher la liste des personnes\n");
        printf("2. Ajouter une personne\n");
        printf("3. Supprimer une personne par badge\n");
        printf("4. Modifier le code secret d'une personne\n");
        printf("5. Simuler le contrôle d'accès via le clavier\n");
        printf("6. Libérer la mémoire et quitter\n");
        printf("7. Sauvegarder la liste dans un fichier\n");
        printf("8. Charger la liste depuis un fichier\n");
        printf("9. Quitter\n");

        // Lire le choix avec validation
        printf("Choix: ");
        while (scanf("%d%c", &choix, &term) != 2 || term != '\n') {
            printf("Choix invalide. Veuillez entrer un nombre valide : ");
            while (getchar() != '\n');  // Vider le tampon
        }

        switch (choix) {
            case 1:
                afficher_liste(head);
                break;
            case 2:
                head = ajouter_personne(head);
                break;
            case 3:
                printf("Entrez le badge de la personne à supprimer : ");
                scanf("%d", &badge);
                head = supprimer_personne(head, badge);
                break;
            case 4:
                printf("Entrez le badge de la personne pour modifier son code secret : ");
                scanf("%d", &badge);
                head = modifier_code(head, badge);
                break;
            case 5:
                controler_acces(head);
                break;
            case 6:
                liberer_liste(head);
                printf("Programme terminé.\n");
                break;
            case 7:
                sauvegarder_liste(head);
                break;
            case 8:
                head = charger_liste(head);
                break;
            case 9:
                printf("Quitter .\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 9);

    return 0;
}

