/*
Crea un alogitmo en el que se pida una letra y a partir de ella se determine
si es una vocla o una consonante
*/
#include <stdio.h>

int main(){

    char letra;

    printf("Ingrese una letra; ");
    scanf("%c",&letra);

    switch (letra)
    {
    case 'a':
        printf("lo ingresado %c es una vocal", letra);
        break;
    case 'e':
        printf("lo ingresado %c es una vocal", letra);
        break;
    case 'i':
        printf("lo ingresado %c es una vocal", letra);
        break;
    case 'o':
        printf("lo ingresado %c es una vocal", letra);
        break;
    case 'u':
        printf("lo ingresado %c es una vocal", letra);
        break;
    
    default:
        printf("Lo ingresado  %c es una consonante.",letra);
        break;
    }
}