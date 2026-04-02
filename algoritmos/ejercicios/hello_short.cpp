#include <iostream>


using namespace std;


int main(){

    char words[10] = "ehlol";
    char hello[10] = "hello";
    char temp;


    for (int i = 0; i < 5; i++)
    {
        if (hello[i] != words[i])
        {
            temp = words[i];
            for (int j = i; j < 5; j++)
            {
                if (hello[i] == words[j])
                {
                    words[i] = words[j];
                    words[j] = temp;
                    break;
                }
                // cout<<words<<endl;
                
            }
            
        }
        
    }

    cout<<words<<endl;
    

    return 0;
}

