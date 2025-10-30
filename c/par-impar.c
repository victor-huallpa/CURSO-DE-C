/*
crea un algoritmo que determone si un numero es par o impar.

*/ 
// &: ampersand
#include <stdio.h>

int main(){

    int number ;

    printf("Ingrese el un numero: ");
    scanf("%d",&number);

    if ((number % 2) == 0)
    {
        printf("El numero %d es par\n", number);

    }else{
        printf("El numero %d es impar\n", number);
    }
    
}