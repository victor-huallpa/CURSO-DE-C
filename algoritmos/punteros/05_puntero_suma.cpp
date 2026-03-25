#include <iostream>
int suma(int *arr, int n);

using namespace std;

int main(){
    //Los elementos de un arreglo tipo int estas diferenciados solo por 4 bytes.
    int arr[5] = {1,2,3,4,5};
    //mumero de elemetos.
    int n = sizeof(arr)/sizeof(int);

    cout<<"La suma del arreglo es: "<<suma(&arr[0], n)<<endl;

    return 0;
}

int suma(int *arr, int n){
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            suma += *arr;
            continue;
        }
        
        suma += *arr + i;
    }
    
    return suma;
}
