#include <stdio.h>


//estructura
struct numeros
{
    int num1;
    float num2;
    double num3;
};

int main(){
    struct numeros number;

    //asignamos valores;
    number.num1 = 45;
    number.num2 = 45.45;
    number.num3 = 45.45454545459;
    printf("%d\n%f\n%f\n",number.num1, number.num2,number.num3);
}