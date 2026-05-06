#include <iostream>
#include <cmath>
using namespace std;


int pow(int a, int b){
    int c = a;
    for (int i = 1; i < b; i++) c*=a;
    return c;
}

int main(){
    int n=5, f=1;

    for(int i = 0; i < n; i++) f*=i+1;
    int arr[f]={0}; 
    int a=1;
    for (int i = 1; i <= n; i++){
        arr[0]+=i*a;
        a=a*10;
    }

    for (int i = 1; i < n; i++){
        arr[i]= arr[i-1]/pow(10,n)+arr[i-1]/10*10;
    }

    
    for (int i = 0; i < f; i++){
        cout << arr[i] << endl;
    }
    return 0;
    
}