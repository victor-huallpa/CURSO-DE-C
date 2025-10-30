/*
JERARQUIA DE OPERADORES LOGICOS
()
!
++
--
*-/-%
+ -
== - != -< - > - <= - >=
&& - ||

*/

/*
La gerarquiera resuelve el codigo dependiendo a como esta acomando y siguiendo 
las ordenes gerarquicas establecidas por el elenguaje.
*/
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    bool dato = true;
    printf("dato = %s\n", dato ? "true" : "false");
    return 0;
}
