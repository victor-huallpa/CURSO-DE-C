# include <iostream>

using namespace std;

class VectorNumero
{
private:
    /* data */
public:
    int suma(int arr[], int n){
        int total = 0;
        for (int i = 0; i < n; i++) total += arr[i];
        return total;
        
    }
};


int main(){
    int v[5] = {1,2,3,4,5};
    VectorNumero vn;
    cout<<"la suma es: "<<vn.suma(v,5)<<endl;
    return 0;
}