#include <iostream>

using namespace std;

int fibIter(int num);

int main () {
    int fac;
    cout<<"Calculando fibonaci de los :";
    cin>>fac;

    cout<<"La suma es: "<<fibIter(fac)<<endl;

    return 0;
}

int fibIter(int num){
    // cout<<num<<"\n";
    int tem = 1;
    int ini= 0;//representa primera iteracion
    int fin = 1;//representa segunda iteracion
    int sig = -1;
    int numM = num;

    if (num < 0)
    {
        numM*=sig;
    }
    

    if (num == 1) return 0;
    if (num == 2) return ini + fin;


    for (int  i = 2; i <= numM; i++)
    {

        
        tem = fin;
        fin = ini + fin;
        ini = tem;
        
    }

    if (num < 0)
    {
        if (num % 2 != 0)
        {
            fin*=sig;
        }    
    }

    return fin;

}

// fib(n) = fib(n-1) + fib(n-2)
