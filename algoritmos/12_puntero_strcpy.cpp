#include <iostream>

using namespace std;

char* strCopy(char *dest, const char * src );

int main(){
    char words[] = "hello";
    char copy[10];
    char *p;
    int cont = 0;
    while (true)
    {
        if (words[cont] == '\0')
        {
            break;
        }

        cout<<"word "<<cont + 1<<": "<<words[cont]<<" ------- copy word "<<cont+1<<": "<<copy[cont]<<endl;
        cont++;
    }
    

    p = strCopy(&copy[0], &words[0]);

    cont = 0;
    

    while (true)
    {
        if (words[cont] == '\0')
        {
            break;
        }

        cout<<"word "<<cont + 1<<": "<<words[cont]<<"------- copy word "<<cont+1<<": "<<copy[cont]<<endl;
        cont++;
    }

    return 0;

}

char* strCopy(char *dest, const char * src ){
    int cont = 0;
    char *srCopy = dest;

    while (true)
    {
        if (*(src + cont) == '\0')
        {
            *(srCopy + cont) = '\0';
            break;
        }

        *(srCopy+cont) = *(src+cont);
        cont++;
    }

    return srCopy;
    
    
}