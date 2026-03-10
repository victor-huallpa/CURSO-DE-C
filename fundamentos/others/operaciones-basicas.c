#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Función para pedir y guardar los dos números usando punteros
void pedir_datos(float *n1, float *n2) {
    printf("Ingrese el primer numero: ");
    scanf("%f", n1); // Se usa n1 para modificar el valor al que apunta

    printf("Ingrese el segundo numero: ");
    scanf("%f", n2); // Se usa n2 para modificar el valor al que apunta
}

// Función que realiza la operación basada en la cadena
float operacion_matematica(char operacion[], float num1, float num2) {
    // Usamos strcmp para comparar la cadena
    if (strcmp(operacion, "suma") == 0) {
        return num1 + num2;
    } else if (strcmp(operacion, "resta") == 0) {
        return num1 - num2;
    } else if (strcmp(operacion, "multiplicacion") == 0) {
        return num1 * num2;
    } else if (strcmp(operacion, "division") == 0) {
        if (num2 == 0) {
            printf("Error: No se puede dividir entre cero.\n");
            return 0.0;
        }
        return num1 / num2;
    } else {
        // En caso de que no se ingrese una operación válida
        printf("Error: Operacion no valida.\n");
        return 0.0;
    }
}

int main() {
    char operacion[20];
    float num1, num2, resultado;

    while (true)
    {

        printf("Ingrese la operacion que desea realizar (suma, resta, multiplicacion, division): ");
        scanf("%s", operacion);

        // Llamamos a la función para obtener los dos números
        pedir_datos(&num1, &num2);

        if (num1 == 0 || num2 == 0)
        {
            break;
        }
        

        // Llamamos a la función que realiza la operación y devuelve el resultado
        resultado = operacion_matematica(operacion, num1, num2);

        printf("El resultado de la operacion es: %.2f\n", resultado);
    }
    printf("\nGracias por usar la calculadora basica\n");
    return 0;
}