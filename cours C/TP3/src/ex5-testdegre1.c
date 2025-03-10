#include <stdio.h>
#include "ex5-degre.h"

int main() {
    float tempC = 100.0, tempK, tempF;

    // Test des conversions
    tempK = CelsiusAKelvin(tempC);
    tempF = CelsiusAFahrenheit(tempC);

    printf("%.2f°C = %.2f K\n", tempC, tempK);
    printf("%.2f°C = %.2f°F\n", tempC, tempF);

    return 0;
}
