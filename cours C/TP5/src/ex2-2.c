/**
 * @author HUGO Chiarel
 * @author JEMAI Axel
 * @date 30/03/2025
 * TP5 - Exercice 2-2 - Pointeurs
 */
#include <stdio.h>

void main()
{
int i,j,k,tmp;
int *pi,*pj,*pk,*ptmp;

i=31 ; j=52 ; k=17;
pi=&i ; pj=&j ; pk=&k;

printf("i=%d j=%d k=%d\n",i,j,k);
printf("*pi=%d *pj=%d *pk=%d\n",*pi,*pj,*pk);

tmp=*pi;
*pi=*pj;
*pj=*pk;
*pk=tmp;

printf("i=%d j=%d k=%d\n",i,j,k);
printf("*pi=%d *pj=%d *pk=%d\n",*pi,*pj,*pk);

ptmp=pi;
pi=pj;
pj=pk;
pk=ptmp;

printf("i=%d j=%d k=%d\n",i,j,k);
printf("*pi=%d *pj=%d *pk=%d\n",*pi,*pj,*pk);
}