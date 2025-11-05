#include <iostream>

using namespace std;
class Contador{
    public: 
    void contarHasta(int n){
        for (int i = 1; i < n; i++){
            cout<<i<<"";        
        }
        cout << endl;
    }

};

int main(){
    Contador c;
    c.contarHasta(5);
    return 0;
}
