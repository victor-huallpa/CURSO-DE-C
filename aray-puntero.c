#include <stdio.h>

int main(){
    char *frutas[3];

    frutas[0] = "pera";
    frutas[1] = "'pera'";
    frutas[2] = "'pera'";
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("\nIngrese una fruta: ");
    //     scanf("%s", &frutas[i]);
    //     // gets(frutas[i]);
    // }

    for(int j = 0; j<3; j++){
        printf(frutas[j]);
    }

    return 0;
}