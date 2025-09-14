/*
Declaracion

Tipo *NOmbreVariablePuntero


-& usamos el anperson'&' para apuntar al espacio de la variable
sacanf("%d", &variable)

*/
#include <stdio.h>

int main(){
    int num;
    int *puntero;

    num=100;
    puntero = &num;

    printf("La dirteccion de memoria es: %p", puntero);

    printf("\nEl valor es: %d", *puntero);
    return 0;
}

