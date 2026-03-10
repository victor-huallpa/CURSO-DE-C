#include <iostream>

using namespace std;

class TablaMultiplicar{
    public:
    void generar(int n){
        int i = 1;

        while(i<=10){
            cout<<n<<" x "<<i<<" = "<< n*i << endl;
            i++;
        }
    }
};

int main(){
    TablaMultiplicar t;
    t.generar(4);

    return 0;
}