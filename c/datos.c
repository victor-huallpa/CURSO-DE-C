#include <stdio.h>

int main(){
    //constante: datos que no se pueden modficar
    

    #define PI 3.14;
    #define EDAD 29;

    //Variable
    float sueldo = 15.456;
    float bono = 4.560;

    sueldo += bono;//suma concatenada

    // %f es para datos flotantes
    printf("Sueldo total: %f", sueldo);

    return 0;
}


