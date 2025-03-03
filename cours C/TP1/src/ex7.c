#include <stdio.h>

int main() {
	float PI = 3.14159;
	float rayon = 0;
	printf("Rentrez le rayon d’un cercle\n");
	scanf("%f", &rayon);

    float perimetre = 2*PI*rayon;
    float surface = (rayon*rayon)*PI;
	
	printf("Le périmètre du cercle est %f\n", perimetre);
	printf("La surface du cercle est %f", surface);
	
}