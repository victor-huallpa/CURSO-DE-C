/*
Realice un programa que calcule el promedio de la nota de 10 estudiantes en un examen final
*/
#include <stdio.h>

int main(){

    float nota, promedio, suma;

    for(int i = 0; i<10; i++){
        printf("ingrese la nota numero %d: ", i+1);
        scanf("%f",&nota);

        suma += nota;
        
        if(i == 9){
            promedio = suma/10;
        }
    }

    printf("el promedio total es: %f", promedio);

    return 0;
}