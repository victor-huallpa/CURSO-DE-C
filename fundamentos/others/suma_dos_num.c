/*
crea un algoritmo simple que sume dos numer oingresados por consola/usuario
*/

#include <stdio.h>
int main(){
    int num1, num2, suma;

    //solicitud de primer numero
    printf("Introduce el primer numero: ");
    scanf("%d", &num1);

    //solicitud del segundo numero
    printf("Introduce el segundo numero: ");
    scanf("%d", &num2);

    //sumamos ambos numeros
    suma = num1 + num2;

    //mostramos el resultado por consola
    printf("El resultado de la suma es: %d\n", suma);

    return 0;
}