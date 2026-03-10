#include <iostream>

using namespace std;

class BusquedaElemento
{
public:
    int elemento(int arr[], int n, int x){
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == x)
            {
                return i;
            }
        }
        return -1;
    }
};

int main(){
    int element[] = {10, 24, 89, 100, 45};
    BusquedaElemento be;
    int indi = be.elemento(element, 5, 5);

    if (indi != -1)
    {
        cout<<"El elemento 10 se encuentra en el indice: "<<indi<<endl;    
    }else{
        cout<<"El elemento que busca no se encuentra dentro del vector.";
    }
    return 0;

}

