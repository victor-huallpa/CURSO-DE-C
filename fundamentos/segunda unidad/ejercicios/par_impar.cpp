#include <iostream>

using namespace std;

class ParImpar{
    public:
        void verficar(int n){
            if(n%2 == 0){
                cout<<n<<" es par "<<endl;
            }
            else{
                cout<<n<<" es impar "<<endl;
            }
        }
};

int main(){
    ParImpar p;

    p.verficar(5);

    return 0;
}