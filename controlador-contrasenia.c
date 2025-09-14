/*
Crea un algoritmo que pida al usuario ingrese una contrasenia y el algoritmo 
verfique si la contraseia es aceprable o no
COSNDIERACIONES:
    - La contrasenia teiene que ser solo numeros
*/

#include <stdio.h>
#include <ctype.h>

int main(){
    //cariables
    char password;

    //solicita password al usuario
    printf("Ingrese password: " );
    scanf("%c", &password);

    if (isdigit(password) == 1)
    {
        printf("Contrasenia valida.\n");
    }
    else{
        printf("Password invalido\n");
    }

    return 0;
}