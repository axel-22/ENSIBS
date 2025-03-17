#include <stdio.h>

void modifier_pointeur(int **pp) {
    int y = 42;
    *pp = &y;  //On change l'adresse contenue dans le pointeur original
}

int main() {
    int x = 10;
    int *p = &x;

    printf("Avant : p pointe sur %d\n", *p);

    modifier_pointeur(&p);  //Passage d'un double pointeur

    printf("Après : p pointe sur %d\n", *p);

    return 0;
}
