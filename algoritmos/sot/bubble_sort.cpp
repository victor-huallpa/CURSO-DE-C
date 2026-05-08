// Algorimot de onamiento lineal(bubble sort) O(n^2)

#include <iostream>
using namespace std;
void bubbleSort(int *num, int n){
    int i;
    int tem;
    // num[4] = 10;
    // cout<<num[4] = 10;
    for (i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            tem = num[j];
            if (tem > num[j + 1])
            {
                num[j] = num[j+1];
                num[j+1] = tem;
            }
        }
        

        
    }
    

}

int main(){
    int numbers[] = {3,5,7,9,9,0};
    bubbleSort(&numbers[0], 6);

    for (int i = 0; i < 6; i++)
    {
        std::cout<<numbers[i]<<"\n";
    }
    
    return 0;
}

