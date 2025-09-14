#include <stdio.h>

int getDate();
const char* anioBisiesto(int anio);

int main() {
    int anio = 1;
    const char *message;

    printf("Bienvenido a nuestra app para calcular si un anio es bisiesto.");
    while (anio != 0) {
        printf("\nIngrese '0' para salir.\n");
        anio = getDate();
        if (anio != 0 && anio > 999) {
            message = anioBisiesto(anio);
            printf("%s\n", message);
            continue;
        } else if (anio <= 999 && anio != 0) {
            printf("\nIngrese un anio valido\nVuelva a intentarlo.\n");
            continue;
        }
    }

    printf("\nGracias por usar nuestra app\n");
    return 0;
}

int getDate() {
    int anio;
    printf("Ingrese el anio a evaluar: ");
    scanf("%d", &anio);
    return anio;
}

const char* anioBisiesto(int anio) {
    if (anio % 400 == 0) {
        return "El anio es bisiesto.";
    } else if ((anio % 4 == 0) && (anio % 100 != 0)) {
        return "El anio es bisiesto.";
    } else {
        return "El anio es comun.";
    }
}
