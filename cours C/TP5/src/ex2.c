/*
* TP 5 : Pointeurs
*
* : lecture de l'adresse des éléments d'un tableau
*/
#include <stdio.h>
#define N 5
void main()
{
 int i;
 int t[N] = {10, 20, 30, 40, 50};

 for(i=0;i<N;i++)
 printf("t[%d] = %d ; &t[%d] = %u\n",i,t[i],i,&t[i]);
}
