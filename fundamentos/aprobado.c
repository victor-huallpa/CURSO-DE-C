/*
crea un algoritmo que ayude a determinar si de 10 estudiantes cula fue la nota mayor cual la menor y cuantos aprovaron
y desaprovaron


*/


#include <stdio.h>
#include <stdbool.h>

int main(){
    //variables de entorno
    int notas[11],notaM = 0, notaMe = 10;
    int aprovados = 0, desaprovados = 0;

    for (int i = 0; i < 10; i++)
    {
        printf("Ingrese la nota numero %d: ", i+1);
        scanf("%d", &notas[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        if (notas[i] > notaM)
        {
            notaM = notas[i];
        }
        if (notas[i] < notaMe)
        {
            notaMe = notas[i];
        }
        if (notas[i] >= 5)
        {
            aprovados++;
        }else{
            desaprovados++;
        }
    }
    
    printf("La mayor nota es: %d\n", notaM);
    printf("La menor nota es: %d\n", notaMe);
    printf("cantidad de aprovados es: %d\n", aprovados);
    printf("Cantidad de desaprovados es: %d\n", desaprovados);

    return 0;
}