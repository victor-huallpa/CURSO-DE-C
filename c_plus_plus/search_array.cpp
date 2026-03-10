#include <iostream>

using namespace std;

int searchArray(int numeros[],int tam, int miNum);
int main (){
    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tam = sizeof(numeros)/sizeof(int);
    int indice;
    int miNum;


    cout << "Ingrese el elemento a buscar: ";
    cin>>miNum;
    indice = searchArray(numeros, tam, miNum);

    if (indice !=  -1)
    {
        cout<<"El numero "<<miNum<<" se encuentra en el indicie "<< indice<<endl;
    }else{
        cout<<"el numeor que estas buscando "<<miNum<<" no se encuentra dentro del array."<<endl;
    }
    
    

    return 0;
}

int searchArray(int numeros[],int tam, int miNum){

    for (int i = 0; i < tam; i++)
    {
        if (numeros[i] == miNum)
        {
            return i;
        }
        
    }
    return -1;
    
}


