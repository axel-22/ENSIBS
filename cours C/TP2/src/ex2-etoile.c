#include <stdio.h>

int demander_nombre() {
    int nombre;
    int input;

    do {
        printf("Entrez un nombre compris [1;20] : ");
        input = scanf("%d", &nombre);
        // Vérifier si scanf a bien lu un entier
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            // Nettoyer le buffer en vidant les entrées invalides
            while (getchar() != '\n');
            continue;  // Recommencer la boucle
        }
        // Vérifier si le nombre est dans la plage [1,20]
        if (nombre < 1 || nombre > 20) {
            printf("Erreur: le nombre doit être compris entre 1 et 20\n");
        }
    } while (input != 1 || nombre < 1 || nombre > 20);

    return nombre;
}

void affichage_ligne(int n) {
    char e = '*';  
    int i = 0;
    int j = 0;
    while(i < n){
        j = 0;
        while(j < n){
            printf("%c", e);
            j = j+1;
        }
        printf("\n");
        i = i+1;
    }
}

void affichage_fleche_droite(int n){
    char e = '*';
    int nb = n*2;
    for (int i = 0; i < nb; i++) {
        if(i <= n){
            for(int j = 0; j < i; j++){
                printf("%c", e);
            }
        }else{
            for(int j = 0;  j < nb-i; j++){
                printf("%c", e);
            }
        }
        printf("\n");
    }
} 

void affichage_fleche_gauche(int n){
    char e = '*';
    char s = ' ';
    int nb = n*2;
    for (int i = 0; i < nb; i++) {
        if(i <= n){
            for(int j = 0; j < n-i; j++){
                printf("%c", s);
            }
            for(int k = 0; k < i; k++){
                printf("%c", e);
            }  
        }else{
            for(int j = 0; j < n-(nb-i); j++){
                printf("%c", s);
            }
            for(int k = 0; k < nb-i; k++){
                printf("%c", e);
            } 
        } 
        printf("\n");
    }
} 

void affichage_pyramide(int n){
    char e = '*';
    char s = ' ';
    for(int i = 0; i < n; i++){
        int et = 2*i+1;
        int es = n - i - 1; 

        for (int j = 0; j < es; j++) {
            printf("%c", s);
        }

        for (int j = 0; j < et; j++) {
            printf("%c", e);
        }

        printf("\n");
    }
}

void affichage_losange(int n) {
    char e = '*';
    char s = ' ';
    int es, et;
    int nb = 2*n-1; 

    for (int i = 0; i < nb; i++) {
        if (i < n) {  
            et = 2 * i + 1;  
            es = n - i - 1;  
        } else {  
            et = 2 * (nb - i - 1) + 1;  
            es = i - n + 1;  
        }

        for (int j = 0; j < es; j++) {
            printf("%c", s);
        }
        for (int j = 0; j < et; j++) {
            printf("%c", e);
        }

        printf("\n");
    }
}

int main() {
    int n = demander_nombre();
    int forme;
    int input;
    printf("1 - Ligne\n");
    printf("2 - Flèche droite\n");
    printf("3 - Flèche gauche\n");
    printf("4 - Pyramide\n");
    printf("5 - Losange\n");
    
    do {
        printf("Choisissez une forme à afficher :\n");
        input = scanf("%d", &forme);
        if (input != 1) {
            printf("Erreur: Veuillez entrer un nombre valide !\n");
            while (getchar() != '\n');
            continue;
        }
        if (forme < 1 || forme > 5) {
            printf("Erreur: le nombre doit être compris entre 1 et 5\n");
        }
    } while (input != 1 || forme < 1 || forme > 5);

    switch (forme) {
        case 1:
            affichage_ligne(n);
            break;
        case 2:
            affichage_fleche_droite(n);
            break;
        case 3:
            affichage_fleche_gauche(n);
            break;
        case 4:
            affichage_pyramide(n);
            break;
        case 5:
            affichage_losange(n);
            break;
        default:
            printf("Erreur : choix invalide !\n");
            break;
    }

    return 0;
}



