#include <iostream>

using namespace std;

int mulSum(int num, int mul){
    if (num == 1)
    {
        return mul;
    }else{
        return mul + mulSum(num-1, mul);
    }
    
}

int main(){

    cout<<"\nLa Multiplicacion es: "<<mulSum(4,6)<<"\n";
    return 0 ;
}