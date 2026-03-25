#include <iostream> 

using namespace std;

void memoryD(int **m, int cap, int n);

int main(){

    int cap = 2;
    int *lista = NULL;
    int cantidad = 1;

    
    int val=0;
    int cont = 0;

    

    while (val != -1)
    {
        memoryD(&lista, cap, cantidad);
        

        cout<<"Ingresse valores: ";
        cin>>val;

        if (val == -1)
        {
            break;
        }
        lista[cont] = val;

        cont ++;
        cantidad ++;
        cap ++;
    }
    



    


    for (int i = 0; i < cont; i++)
    {
        cout<<"\nvalor: "<<*(lista + i)<<endl;
    }
    
    

    // cout<<"Ingresse valores: ";
    // cin>>val;

    return 0;
}

void memoryD(int **m, int cap, int n){
    if (*m == NULL)
    {
        *m = new int[cap];
    }else{
        int* arr = *m;
        *m = new int[cap];
        //copiamos los elementos
        for (int i = 0; i < n; i++)
        {
            (*m)[i] = *(arr + i);
        }
        
       
        delete[] arr;

    }
} 



