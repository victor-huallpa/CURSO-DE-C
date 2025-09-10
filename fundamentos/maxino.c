#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>  // ✅ en Linux
#include <unistd.h>   // ✅ para STDIN_FILENO

float maximo(float num1, float num2);
float entrada(int contador);

char getch(void) {
    struct termios oldattr, newattr;
    char ch;

    // Guardar la configuración actual del terminal
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;

    // Desactivar modo canónico y eco
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    // Leer un carácter
    ch = getchar();

    // Restaurar configuración original
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

int main() {
    float num1, num2, mayor;
    bool inspec = true;
    int contador = 1;
    char tecla;

    while (inspec) {
        if (contador == 1) {
            num1 = entrada(contador);
            contador = 2;
            continue;
        } else if (contador == 2) {
            num2 = entrada(contador);
            contador = 0;
            continue;
        }
        mayor = maximo(num1, num2);
        printf("El máximo número es: %.2f\n\n", mayor);

        printf("Presiona ESPACIO para calcular de nuevo otros números ");
        printf("o cualquier otra tecla para salir: \n");
        tecla = getch(); // no requiere Enter
        if (tecla == 32) { // 32 = espacio
            contador = 1;
            system("clear");
        } else {
            printf("Gracias por usar el programa para calcular el maximo de dos numero\n");
            inspec = false;
        }
    }
    return 0;
}

float maximo(float num1, float num2) {
    if (num1 < num2) {
        return num2;
    } else if (num1 > num2) {
        return num1;
    } else {
        return num1; // si son iguales, devolvemos cualquiera
    }
}

float entrada(int contador) {
    float numero;
    printf("Ingrese el %d° número: ", contador);
    scanf("%f", &numero);

    // Limpiar buffer
    while (getchar() != '\n');

    return numero;
}
