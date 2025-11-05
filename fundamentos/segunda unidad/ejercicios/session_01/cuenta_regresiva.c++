#include <iostream>

using namespace std;

class CuentaRegresiva {
    public:

    void iniciar(int n){
        do{
            cout<<n<<" \n";
            n--;
        }while(n>=0);
        cout << endl;
    }
};

int main(){
    CuentaRegresiva c;
    c.iniciar(5);
    return 0;
}