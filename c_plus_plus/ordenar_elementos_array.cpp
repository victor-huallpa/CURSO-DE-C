#include <iostream>

using namespace std;

void
 ordenar(int arreglo[], int tam);
int main(){
    int arreglo[] = {4, 6, 2, 1, 3, 5, 9, 7, 8};
    int tam = sizeof(arreglo)/sizeof(int);

    ordenar(arreglo, tam);
    for (int i = 0; i < tam; i++)
    {
        cout<<arreglo[i]<<endl;
        
    }

    return 0;
}
void ordenar(int arreglo[], int tam){
    int temporal;

    for (int i = 0; i < tam-1; i++)
    {
        for (int j = 0; j < tam-1; j++)
        {
            if (arreglo[j]>arreglo[j+1])
            {
                temporal = arreglo[j];

                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = temporal;
            }
            
        }
        
    }
    
}
