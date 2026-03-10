#include <iostream>
using namespace std;

class CadenaInversa
{
public:
    string invertir(string cadena){
        string r = "";
        for (int i = cadena.size()-1; i >= 0; i--) r += cadena[i];
        return r;
    }
};

int main(){
    CadenaInversa ci;
    cout<<"la inverso de universidad es: "<<ci.invertir("universidad")<<endl;
    return 0;
}

