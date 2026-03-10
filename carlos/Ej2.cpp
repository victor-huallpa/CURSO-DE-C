#include <iostream>
using namespace std;
class ClasificarNotas{
    public:
    char clasificar(int nota){
        if (nota>=18)return 'A';
        else if (nota>=15)return 'B';
        else if (nota>=12)return 'C';
        else if (nota>=10)return 'D';
        else return 'F';
    }
};

int main(){
    ClasificarNotas c;
    int n;
    cout<<"Ingrese N de notas: ";cin>>n;
    int nota[n];
    for(int i=0;i<n;i++){
        while(){
            cout<<"Nota "<<i+1<<": ";cin>>nota[i];
        }
    }
}