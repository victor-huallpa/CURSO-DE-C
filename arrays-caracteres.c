#include <stdio.h>
#define NUM 5
int main(){
    char apellido[NUM] = {'L','o','p','e','\0'};//teenre en cuenta que si se sobre pasa el arreglo puede generar que se imprima sobre este loq eu le sigue
    char nombre[NUM] = "juan";//considerar que esto tambien es un array, ya que los caracteres se almacenan en ciertas celdas de una lista/arreglo
    printf("%s\n",apellido);
    printf("%s\n",nombre);
    return 0;
}