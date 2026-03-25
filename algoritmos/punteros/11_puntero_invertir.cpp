#include <iostream>
using namespace std;

void invertir(int *p, int n);

int main(){
    int lista[] = {1,2,3,4,5,6};
    int n = sizeof(lista)/sizeof(int);

    for (int i = 0; i < n; i++)
    {
        cout<<"valor "<<i+1<<": "<<lista[i]<<endl;
    }
    invertir(&lista[0], n);
    for (int i = 0; i < n; i++)
    {
        cout<<"valor "<<i+1<<": "<<lista[i]<<endl;
    }

    return 0;
}

void invertir(int *p, int n){
    int val;
    int inver = n - 1;

    for (int i = 0; i < (n/2)+1; i++)
    {
        if (i == inver)
        {
            break;
        }
        
        val = *(p+inver);
        *(p+inver) = *(p+i);
        *(p+i) = val;
        
        inver--;
    }
}