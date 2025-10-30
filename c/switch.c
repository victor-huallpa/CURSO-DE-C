/*
Crea un algoritmo que al ingresar un nuermo entre 1-7 se determine 
que dia de la semana es.
*/

#include <stdio.h>

int main(){
    int dia;

    printf("Ingrese un el numero del dia de la semana en que se encuentra: ");
    scanf("%d",&dia);

    switch (dia)
    {
    case 1:
        printf("Hoy es el dia Lunes.\n");
        break;
    case 2:
        printf("Hoy es el dia Martes.\n");
        break;
    case 3:
        printf("Hoy es el dia Miercoles.\n");
        break;
    case 4:
        printf("Hoy es el dia Jueves.\n");
        break;
    case 5:
        printf("Hoy es el dia Viernes.\n");
        break;
    case 6:
        printf("Hoy es el dia Sabado.\n");
        break;
    case 7:
        printf("Hoy es el dia Domingo.\n");
        break;
    
    default:
        printf("lo que ingreso %d no corresponde a un dia de la semana entre 1-7.\n", dia);
        break;
    }
}