#include <iostream>
#include <ctime>


using namespace std;


int main(){

    srand(time(0));
    int ran = rand() % 10 +1;

    cout<<ran<<endl;

    return 0;
}