/*
Crea un lgoritmo que calcule el descuento que le corresponde a un producto
1. mosto de compra
2. descuento a aplicar

*/

#include <stdio.h>
float calcularDescuento(float compra, int descuento);
int main(){
    float compra, total;
    int descuento;

    printf("Ingrese el monto de su compra: ");
    scanf("%f", &compra);

    printf("Ingrese el valor de descuento en porcentaje: ");
    scanf("%d", &descuento);

    total = calcularDescuento(compra, descuento);

    printf("El precio a pagar es de: %.2f\n", total);
    return 0;

}

float calcularDescuento(float compra, int descuento){
    float nuevoPrecio;
    nuevoPrecio = compra*((float)(100-descuento)/100);

    // nuevoPrecio = compra - (compra*((float)descuento/100));

    return nuevoPrecio;
}

//consideremos que solo puedemos retornar el descuetno y despues operar el resultado en otro lado.
