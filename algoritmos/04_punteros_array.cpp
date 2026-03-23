#include <iostream>
void iter(int *arr);

using namespace std;

int main(){
    int arr[5] = {1,2,3,4,5};
    int *pnt = &arr[0]; 

    // cout<<&arr<<endl;
    // cout<<&arr[1]<<endl;
    
    //cuantos bytes ocupa un dato tipo int (4 bytes)
    // cout<<sizeof(int)<<endl;

    
    // iter(arr);

    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            cout<<*pnt<<endl;
            continue;
        }
        
        cout<<*pnt + i<<endl;
    }
    

    return 0;

}

void iter(int *arr){
    for (int i = 0; i < 5; i++)
    {
        cout<<*arr + i<<endl;

    }
    
}