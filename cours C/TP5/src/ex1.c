/*
* TP 5 : Pointeurs
*
* lecture de l'adresse d'une variable
*/
#include <stdio.h>
void main()
{
 int i,j;

 i = 5;
 j = 12 ;
 printf("La variable i est située à l'adresse %u et vaut %d\n",&i,i);
 printf("La variable j est située à l'adresse %u et vaut %d\n",&j,j);
}
