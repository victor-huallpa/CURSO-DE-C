#include <iostream>

using namespace std;

class Triangulo
{
// cosntancia valida el tipo de triangulo
public:
    bool esValido(int a, int b, int c){
        return (a+b > c && a +c > b && b+c > a);
    }
};

int main(){
    Triangulo t;
    cout << (t.esValido(3,4,5 ) ? "valido" : "No es valido")<<endl;

    return 0;
}