/*
crea un algorimto que determine si un elemento es true y en caso no lo sea siga en un bucle infinito
*/

#include <stdio.h>
#include <stdbool.h>

int main(){
    char bolean;
    int num;
    num = 0;
    bolean = true;
    while (bolean)
    {
        if(num < 10){
            printf("jaja estas atrapado\n");
        }else{
            printf("esta fuera");
            bolean = false;
        }

        num+=1;
    }

    return 0;
    
}