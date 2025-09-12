/*
crea un algorimti que saque el pormedio de nuermos almacenados en un array, cosnidera qe estos nuemro deben ser ingrasdos
por el usuarioy si ingresa cero estos datos deben ser promediados

*/

#include <stdio.h>

int main(){

    int controller=1, tamanio=2, contador=0, prmedio;
    int lista[tamanio];

    while (controller != 0)
    {
        printf("ingrese un numero: ");
        scanf("%d", lista[contador]);

        if(lista[contador] == 0){
            controller = 0;
            for (int i = 0; i < contador-2; i++)
            {
                
            }
            
            break;
        }
        contador++;
        tamanio++;
    }
    
}