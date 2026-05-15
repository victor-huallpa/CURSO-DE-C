#include <iostream>

using namespace std;

int cuentRe(int num);

int main () {
    int fac;
    cout<<"Calculando factorial...\n";
    cin>>fac;

    cout<<"La cuenta es: \n"<<cuentRe(fac)<<endl;

    return 0;
}

int cuentRe(int num){
    cout<<num<<"\n";
    if (num == 2)
    {
       return 1 ;
    }else{
        return cuentRe(num -1);
    }
    
}
