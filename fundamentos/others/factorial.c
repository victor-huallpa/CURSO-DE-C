/*
se calcula el factorial de un numer oentero no negativo. El factorial de un numero n es el prpcitro de todods los enteros positivos desde 1 hasta n.
*/

#include <stdio.h>

int main(){
    int num,i;
    long long factorial = 1;

    //solicituar al usuario de ingresar
    printf("Introduce un numero entero no negativo: ");
    scanf("%d", &num);

    //si el numer oes negativo, mostrar un mensaje de error
    if(num < 0){
        printf("Erro! el factorial de un numero negatico no existe");
    }
    else
    {
        //calcular el facorial usnado un gucle for
        for ( i = 1; i < num; i++)
        {
            factorial*= i;
        }
        printf("El factorial de %d es: %lld\n", num, factorial);
        
    }
    return 0;
}