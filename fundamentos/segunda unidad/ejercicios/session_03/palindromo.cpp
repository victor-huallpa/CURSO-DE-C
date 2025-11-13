#include <iostream>
using namespace std;

class Palindromo
{
public:
    bool esPalindromo(string s){
        int i = 0, j= s.size()-1;
        while (i < j)
        {
            if(s[i] != s[j])return false;
            i++,j--;
        }
        return true;
    }

};

int main(){
    Palindromo p;
    cout<<(p.esPalindromo("12321")? "Es palindromo": "No es palindromo") <<endl;
    return 0;
}


