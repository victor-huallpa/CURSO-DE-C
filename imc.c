/*
Crea un algoritmo que determine el indice de masa corporal ICM
a apartir de la talla en cm y peso en kg ingresados por consola
*/
// formula del IMC peso/altura**2
#include <stdio.h>

int main(){

    float peso, altura, imc;

    printf("Ingrese su peso en kilogramos: ");
    scanf("%f",&peso);

    printf ("Ingrese su estatura en metros: ");
    scanf("%f",&altura);

    imc = peso/(altura*altura);

    if (imc < 18.50)
    {
        printf("Estas bajo de peso(estas sufriendo de desnutricion).");
    }else if ((imc >= 18.50) &&( imc < 25))
    {
        printf("Tu imc es ideal sige con esa dieta alimenticia");
    }else if ((imc >= 25) && (imc < 30))
    {
        printf("Estas sufriendo de sobrepeso(recomendamos que balancees tu dieta).");
    }else if ((imc >= 30) && (imc <35))
    {
        printf("Tu imc indica que estas en obecidad leve(ve con tu doctor para que te recomiende una dieta).");
    }else if (imc >= 35)
    {
        printf("Recomendamos que visite urgentemente a su doctor para que le indicque una dieta espesifica para uds.");
    }else{
        printf("Lo siento estamos teniendo problemas para calcular adecaudamente su imc");
    }
    
    
    
    
    
    printf("\ntu imc es de: %.2f\n", imc);

}