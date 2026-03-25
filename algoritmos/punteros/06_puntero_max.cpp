#include <iostream>

int maximo(int *arr, int n);

using namespace std;

int main(){
    int arr[5] = {2,2,10,9,8};
    int n = sizeof(arr)/sizeof(int);

    cout<<"El numero mayor del array es: "<<maximo(&arr[0], n)<<endl;
    return 0;
}

int maximo(int *arr, int n){
    int max = *arr;
    // cout<<max<<endl;
    for (int i = 1; i < n; i++)
    {
        if (max < *(arr + i))
        {
            max = *(arr + i);
        }   
    }
    
    return max;
}