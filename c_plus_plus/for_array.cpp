#include <iostream>

using namespace std;

int main(){
    string estudiantes[] = {"joge", "maria", "pedro","vech"};

    

    // calculamos la longitud del array
    int longitud = sizeof(estudiantes)/sizeof(string);

    //iteramos el array con un bucle for
    for (int i = 0; i < longitud; i++)
    {
        cout<<estudiantes[i]<<endl;
    }

    char notas[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    longitud = sizeof(notas)/sizeof(char);

    for (int i = 0; i < longitud; i++)
    {
        cout<<notas[i]<<endl;
    }
    
    string nombre = "vech";

    longitud = sizeof(nombre)/sizeof(nombre[0]);

    cout<<longitud<<endl;
    cout<<nombre[0]<<endl;


    // para este caso usamos length(), porque la forma de calcular la longitud de elementos de un strng o un tipo de carecter especifioc no es igual que como se calcula con sizeof
    

    for (int i = 0; i < nombre.length(); i++)
    {
        cout<<nombre[i]<<endl;
        
    }
    
    
}