#include <iostream>

int main(){
    int n = 5;
    int vector[n] = {0};

    for (int i = 0; i < n; i++)
    {
        std::cout<<vector[i];
    }
    std::cout<<std::endl;
    n = 10;
    vector[n] = {0};
        for (int i = 0; i < n; i++)
    {
        std::cout<<vector[i]<<std::endl;
    }

    return 0;
}