#include <stdio.h>

int main(){
    char hello[7] = {'h','e','l','l','o','\0'};

    for (int i = 0; i < 6; i++)
    {
        printf("%c\n",hello[i]);
    }

    return 0;
    
}