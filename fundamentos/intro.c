// crea un algotirmo que intercabe los valores de dods varibales

#include <stdio.h>

void main(){
    int num1, num2, tp;

    num1 = 7;
    num2 = 9;

    printf("num 1: %d \nnum 2: %d", num1, num2);

    tp = num1;
    num1 = num2;
    num2 = tp;
    printf("\nnum 1: %d\nnum 2: %d\n", num1, num2);

}