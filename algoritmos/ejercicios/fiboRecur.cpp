#include <iostream>

using namespace std;

int fibRecur(int num);

int main () {
    int fac;
    int numM;
    cout<<"Calculando fibonaci de los :";
    cin>>fac;

    numM = fac;
    
    if (fac<0)
    {
        numM*=-1;
    }
    

    int numFib = fibRecur(numM);

    if (fac < 0)
    {
        if (fac % 2 != 0) numFib*=-1;
        
    }
    cout<<"La suma es: "<<numFib<<endl;

    return 0;
}

int fibRecur(int num){
    // cout<<num<<"\n";
    
    if(num == 0) return 0;
    if(num == 1) return 1;
    return fibRecur(num - 1) + fibRecur(num-2);
    

}

// fib(n) = fib(n-1) + fib(n-2)
