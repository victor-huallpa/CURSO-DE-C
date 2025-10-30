#include <stdio.h>

int main(){
    //OPERADORES MATEMATICOS
    /*
    SUMA: +
    RESTA: -
    MULTIPLICACION: *
    DIVICION: /
    RESTO: %
    */

    int num1 = 5;
    int num2 = 2;

    float suma = num1 + num2;
    float multipicacion = num1 * num2;
    float divicion = num1 / num2;
    float resta = num1 - num2;
    float modulo = num1 % num2;

    printf("la suma de %d y %d es: %f\n", num1, num2, suma);
    printf("la resta de %d y %d es: %f\n", num1, num2, resta);
    printf("la multiplicacion de %d y %d es: %f\n", num1, num2, multipicacion);
    printf("la divicion de %d y %d es: %f\n", num1, num2, divicion);
    printf("la modulo de %d y %d es: %f\n", num1, num2, modulo);
    return 0;
}