/*
crea una duncion que calcule el area de un triangulo
*/

#include <stdio.h>

// declaramos la funcion
int areaTriangulo(int base, int altura);

int main(){
    int base, altura, area, area2;

    printf("Ingresse la altura del triangulo: ");
    scanf("%d", &altura);

    printf("Ingresse la base del triangulo: ");
    scanf("%d", &base);

    area = areaTriangulo(base, altura);

    printf("el area del triangulo con base de %d y altura de %d es de: %d metros\n", base, altura, area);

    base = 10;
    altura = 5;
    area = areaTriangulo(base, altura);
    printf("el area del triangulo con base de %d y altura de %d es de: %d metros\n", base, altura, area);

    base = 20;
    altura = 5;
    area = areaTriangulo(base, altura);
    printf("el area del triangulo con base de %d y altura de %d es de: %d metros\n", base, altura, area);

    area2 = areaTriangulo(13,7);
    printf("el area del triangulo con base de 13 y altura de 7 es de: %d metros\n", area2);
    return 0;
}

int areaTriangulo(int base, int altura){
    int resultado;
    resultado = (base*altura)/2;

    return resultado;
}
