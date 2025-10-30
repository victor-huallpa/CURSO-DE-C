/*
crea un algoritmo que calcule el interes compuesto
*/

#include <stdio.h>
#include <stdbool.h>

int main(){
    float actual, inversion,interes, ganancia;
    int years, n = 1;

    while (n == 1)
    {
        printf("Ingrese monto que tiene invertido actualmente: ");
        scanf("%f", &actual);

        if(actual >= 0){
            break;
        }
        printf("Ingrese un dato correcto. \n");
    }

    while (true)
    {
        printf("Ingrese el monto adicional por ano: ");
        scanf("%f", &inversion);
        if(inversion >= 0){
            break;
        }
        printf("Ingrese datos correctos!\n");
    }
    while (true)
    {
        printf("Ingrese los anos a invertir: ");
        scanf("%d", &years);
        if(years > 0){
            break;
        }
        printf("Ingrese datos correctos!\n");
    }

    while (true)
    {
        printf("Ingrese el interes por ano: ");
        scanf("%f", &interes);
        if(interes >= 0){
            break;
        }
        printf("Ingrese datos correctos!\n");
    }
    
    
    //calculando el interes compuesto
    double total = actual;
    ganancia = (1+(interes/100));

    for(int i = years; i>0;i--){
        total += inversion;
        total = total +(interes*total/100);

    }


    printf("Monto ganado en %d anos es %.2lf.",years, total);

    return 0;

}