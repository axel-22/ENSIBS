#include <stdio.h>

void hw(); // Le prototype ici

int main() {
    hw(); // OK, le compilateur connaît maintenant la fonction
    return 0;
}

void hw() {
    printf("Hello world\n");
}
