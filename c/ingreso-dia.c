/*
crea un algoritmo donde se calcule el ingreso total del dia
*/

#include <stdio.h>

int main(){
    float venta, total = 0;
    int dia, nventa;
    nventa = 1;
    venta = 0;
    // dia = 0; //inicio de dia 0

    printf("Ingrese cuantas ventas realizo en el dia: ");
    scanf("%d",&dia);

    do{
        printf("ingrese la venta %d: ", nventa);
        scanf("%f",&venta);

        nventa++;
        total += venta;
        dia--;
    }while (dia > 0);
    
    printf("venta total: %.2f", total);

    return 0;
}