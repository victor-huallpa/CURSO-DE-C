#include <iostream>

using namespace std;

class PromedioNotas
{

public:
    float promedio(float notas[], int n){
        float suma = 0;
        for (int i = 0; i < n; i++) suma += notas[i];
        float total = suma/n;
        return total;
    }
};

int main(){
    float notas[] = {12,15,17,02,14.5,20};
    int cant = 6;
    PromedioNotas pn;
    cout<<"El promedio de notas es: "<<pn.promedio(notas, cant)<<endl;
    return 0;
}