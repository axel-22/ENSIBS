#include <stdio.h>
#include "ex5-degre.h"

// Conversion Celsius → Kelvin
float CelsiusAKelvin(float celsius) {
    return celsius + 273.15;
}

// Conversion Celsius → Fahrenheit
float CelsiusAFahrenheit(float celsius) {
    return (9.0 / 5.0) * celsius + 32.0;
}

// Conversion Kelvin → Celsius
float KelvinACelsius(float kelvin) {
    if (kelvin < 0) {
        printf("Erreur : Un Kelvin ne peut pas être négatif !\n");
        return -1; // Valeur d'erreur
    }
    return kelvin - 273.15;
}

// Conversion Fahrenheit → Celsius
float FahrenheitACelsius(float fahrenheit) {
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}
