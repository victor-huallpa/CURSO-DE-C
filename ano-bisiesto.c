/*
Crea un algoritmo que nos ayude a determinar si el ano ingresado por el 
usuario es bisiesto o no.
CONSIDERACIONES PARA ANO BISIESTO:
    - Numero de 4 cifras
    - Son multiplos de 4 pero no multiplos de 100
    - Son muliplos de 400
*/

#include <stdio.h>

int main(){
    //variables
    int anio;

    //solicitamos que ingrese el ano al usuario
    printf("Ingrese el anio a evaluar: ");
    scanf("%d", &anio);

    //calculamos si el anio es bisiesto o no
    if(anio %400 == 0){
        printf("El anio es Bisiesto.");
    }
    else if ((anio % 4 == 0) && (anio % 100 != 0))
    {
        printf("El anio es bisiesto.");
    }else{
        printf("El anio es comun.");
    }
    

    return 0;
}