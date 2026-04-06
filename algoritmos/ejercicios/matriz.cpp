#include <iostream>


using namespace std;

int main (){

    int numeros[][3] = {{2, 12},{11,3},{12,5}};

    for (int i = 0; i < 3; i++)
    {
        /* code */
        for (int j = 0; j < 2; j++)
        {
            cout<<numeros[i][j];
        }
        cout<<endl;
    }
    

    return 0;
}