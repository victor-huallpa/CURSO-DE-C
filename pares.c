/*
Escribe todos los numeros pares entre 1 y 100

*/
#include <stdio.h>

int main(){

    // for (int i = 1; i < 100; i += 2)//en una sla linea se peude realizar la busqueda de inmpoares.
    // {
    //     printf("%d\n",i);
    //     // if (i == 98)
    //     // {
    //     //     printf("%d",i+2);
    //     // }
        
    // }

    for (int i = 1; i <= 100; i++)
    {
        if (i%2!=0)//podemos comparar que sea diferente de sero o que sea igua la 1 para los impares.
        {
            printf("%d\n",i);
        }
        
    }
    

    return 0;
    
}