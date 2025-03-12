/*
*
*/
#include <stdio.h>
void main()
{
int i; /* (1) */
int *p; /* (2) */
i = 5;
p = &i; /* (3) */
printf("Le pointeur p designe la donnée située à l'adresse %u\n",p);
printf("La donnée pointée par p vaut %d\n",*p);
*p = 12 ; /* (4) */
printf("La variable i contient la valeur %d\n",i);
}