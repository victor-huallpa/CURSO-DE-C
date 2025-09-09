#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
float maximo( float num1, float num2);
int main(){
    float num1, num2, mayor;
    bool inspec = true;
    
    while(inspec){

    }

    mayor = maximo(num1, num2);

    printf("el maximo numero es: %.2f", mayor);

    return 0;
}

float maximo( float num1, float num2){
    float retorno;
    if(num1 < num2){
        return num2;
    }else if (num1>num2)
    {
        return num1;
    }else{
        return 0,0;
    }
}

float entrada(int contador){
    float numero;
    
    printf("Ingrese el primer numero: ");
    scanf("%f", &numero);
}
