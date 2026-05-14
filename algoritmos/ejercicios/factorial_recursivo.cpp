#include <iostream>

using namespace std;

int factorial(int num);

int main () {
    cout<<factorial(5)<<endl;

    return 0;
}

int factorial(int num){
    if(num == 0){
        return 1;
    }else{
        return num * factorial(num -1);
        
    }
}
