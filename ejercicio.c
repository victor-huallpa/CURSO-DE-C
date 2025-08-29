/*
Realice un programa que determine cual es la nota final de un alumno
en una materia trenido en cuenta que la nota final es el promedio de 2 examenes.
(Obtener el promedio de los 2 examenes)
*/


#include <stdio.h>

int main(){
    float examen1, examen2;

    //scanf es para pedir datos por consola
    printf("Ingrese la nota del primer examen: ");
    scanf("%f",&examen1);
    printf("Ingrese la nota del segundo examen: ");
    scanf("%f",&examen2);

    float promedio;
    promedio = (examen1 + examen2)/2;

    // %.numf es para la cantidad de digitos que queires que tenga el flotante
    printf("El promeido del alumno es: %.2f", promedio);

    return 0;
}