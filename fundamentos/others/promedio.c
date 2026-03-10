/*
crea un algorimti que saque el pormedio de nuermos almacenados en un array, cosnidera qe estos nuemro deben ser ingrasdos
por el usuarioy si ingresa cero estos datos deben ser promediados

*/

#include <stdio.h>

int main(){

    int controller=1, tamanio=2, contador=0;
    float  promedio=0;
    int lista[tamanio];

    //ingresamos en bucle apra validar controller
    while (controller != 0)
    {
        //solicitud de datos al usuario
        printf("ingrese un numero: ");
        scanf("%d", &lista[contador]);//almacenamiento de datos en array

        //verificamos que si el usuario ingreso cero para calcular el promedio
        if(lista[contador] == 0){
            // realizamos suma de todos los valores de larray
            for (int i = 0; i < contador; i++)
            {
                promedio += lista[i];
            }
            //calculamos promedio
            promedio = promedio/(contador);
            controller = 0;//controlador ifualamos a cero para cerrar el bucle
            continue;
            
        }

        // en caso el usuario no ingreso cero el contado y tamnio de array se aplia
        contador++;
        tamanio++;
    }
    // printf("%d\n",lista);
    // printf("%d\n", contador);
    //imprimimos el resulado del promedio
    printf("\nEl promedio es: %.2f", promedio);
    return 0;
}