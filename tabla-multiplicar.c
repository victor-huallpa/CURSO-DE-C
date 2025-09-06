/*
crea un algoritmo que realizce la tabla de multiplicaar del 1 al 12
*/

#include <stdio.h>

int main(){
    int tabla;
    printf("Ingrese la tabla que quiere realizar: ");
    scanf("%d",&tabla);

    for(int i = 1; i <=12; i++){
        printf("%d x %d = %d\n", i, tabla,i*tabla);
    }
}