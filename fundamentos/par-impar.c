/*
crea un algoritmo que determine si el numero ingresado es par o impar#
*/
#include <stdio.h>

int main(){

    int num, contador = 0;

    //solicitamos un nuemor para verifcar
    printf("Ingrese un numero: ");
    scanf("%d", &num);

    //verificamos si el numero es primo
    for(int i = 2; i<= num; i ++){
        if(num%i == 0){
            contador +=1;
        }
        if(contador == 2 && i == num){
            printf("El numero %d es primo", num);
        }else if (contador > 2 )
        {
            
        }
        
    }

}