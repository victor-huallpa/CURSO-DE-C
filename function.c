/*
crea una duncion que calcule el area de un triangulo
*/

#include <stdio.h>

// declaramos la funcion
int areaTriangulo(int base, int altura);

int main(){
    int base, altura, area;

    printf("Ingresse la altura del triangulo: ");
    scanf("%d", &altura);

    printf("Ingresse la base del triangulo: ");
    scanf("%d", &base);

    area = areaTriangulo(base, altura);

    printf("el area del triangulo con base de %d y altura de %d es de: %d metros\n", base, altura, area);

    return 0;
}

int areaTriangulo(int base, int altura){
    int resultado;
    resultado = (base*altura)/2;

    return resultado;
}
