#include <iostream>

using namespace std;
 
class MayorDeTres{
    public:
    int mayor(int a, int b, int c){
        if (a>=b && a>=c)return a;
        else if (b>=a && b>=c)return b;
        else return c;
    }
};

int main(){
    MayorDeTres m;
    cout <<"Mayor: "<< m.mayor(7,3,9)<<endl;

    return 0;
}

