/*
los array son conjunto de datos alnacenados en memoria
*/

#include <stdio.h>
#define TAMANIO 5//definimos la constante para el tamanio del array
int main(){
    //formas de definir un array con espacio de alamcenamiento definido
    int arreglo1[5];
    int arreglo2[TAMANIO];
    int arreglo3[] = {0, 1, 2, 3, 4};

    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\nIngrese el dato %d: ", i+1);
        scanf("%d", &arreglo2[i]);
    }
    printf("Datos del array:");
    for (int i = 0; i < TAMANIO; i++)
    {
        printf("\narreglo[%d] = %d ",i,  arreglo2[i]);
    }
    

    return 0;
}