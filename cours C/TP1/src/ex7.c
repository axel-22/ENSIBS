/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP1 - Exercice 7 - Affiche le périmètre et la surface d’un cercle
 */
#include <stdio.h>

int main() {
	float PI = 3.14159; // Déclaration de la constante PI
	float rayon = 0; 	// Déclaration de la variable rayon
	printf("Rentrez le rayon d’un cercle\n");
	// Demande à l'utilisateur de rentrer un rayon
	// Vérifier que l'utilisateur rentre bien un float ou un entier
	int input;
	do{
		input = scanf("%f", &rayon);
		if(input != 1){
			printf("Veuillez rentrer un nombre\n");
			while(getchar() != '\n'); // Vide le buffer pour éviter une boucle infinie
		}
		else if(rayon <= 0){
			printf("Veuillez rentrer un nombre positif\n");
		}
	}while(input !=1 || rayon <= 0); // Boucle tant que l'utilisateur ne rentre pas un nombre

    float perimetre = 2*PI*rayon; // Calcul du périmètre
    float surface = (rayon*rayon)*PI; // Calcul de la surface
	
	printf("Le périmètre du cercle est %f\n", perimetre);
	printf("La surface du cercle est %f\n", surface);

	return 0;
}