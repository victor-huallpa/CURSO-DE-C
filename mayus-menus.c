/*
Crea un algoritmo que pida la usuario una cadena de carecteres, y las convierta de mayusaculas a minusculas

*/

#include <stdio.h>
#include <ctype.h>

int main(){
    char text[80], *pcadena;

    //solicita mensaje a usuario
    puts("Ingrese una frase: ");
    gets(text);
    // printf("Ingres mensaje: ");
    // scanf("%c", &text);
    pcadena = text;

    printf("La cadena en minusculas es: ");
    while (*pcadena != '\0')
    {
        printf("%c", tolower(*pcadena++));
    }
    

    return 0;
}