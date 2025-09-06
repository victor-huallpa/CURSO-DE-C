// usando GETS Y PUTS

#include <stdio.h>

#define NUM 5

int main(){
    char nombre[NUM];

    printf("Ingrese el nombre: ");
    gets(nombre);//almacenar los datos del arreglo// omitiendo scanf
    puts(nombre);//Mostrar los datos de larreglo

    return 0;
}