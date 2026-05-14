#include <iostream>

using namespace std;

int factorial(int num){
    if (num == 0)
    {
        return 1;
    }else{
        return num * factorial(num-1);
    }
    
}

int main(){

    cout<<"\nEl factorial es: "<<factorial(12)<<"\n";

    return 0;
}




