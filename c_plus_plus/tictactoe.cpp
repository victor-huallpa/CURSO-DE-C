#include <iostream>

using std::cout, std::cin, std::endl;

char eleccionUsuario();
char eleccionComputadora();
void mostrarEleccion(char eleccion);
void elegirGanador(char jugador, char computadora);

int main (){

    char jugador, computadora;

    jugador = eleccionUsuario();
    cout<<"Jugador: ";
    mostrarEleccion(jugador);

    computadora = eleccionComputadora();
    cout<<"Computadora: ";
    mostrarEleccion(computadora);

    elegirGanador(jugador, computadora);


    return 0;
}

char eleccionUsuario(){

    char jugador;
    cout<<"*****************************\n";
    cout<<"Roca-Papel-tigera | Juagador\n";
    cout<<"*****************************\n";
    do
    {
        cout<<"'r' para roca\n";
        cout<<"'p' para papel\n";
        cout<<"'t' para tijera\n";
        cout<<"Elige uno: \n";
        cin>>jugador;

    } while (jugador != 'r' && jugador != 'p' && jugador != 't');
    


    return jugador;
}

char eleccionComputadora(){
    srand(time(0));
    int num = rand() % 3 + 1;

    switch (num)
    {
    case 1: return 'r';
    case 2: return 'p';
    case 3: return 't';
    }
    return 0;
}

void mostrarEleccion(char eleccion){
        switch (eleccion)
    {
    case 'r':
        cout<<"Roca\n";
        break;
    case 'p':
        /* code */
        cout<<"Papel\n";
        break;
    case 't':
        /* code */
        cout<<"Tigera\n";
        break;
    
    // default:
    //     break;
    }
}

void elegirGanador(char jugador, char computadora){
    switch (jugador)
    {
    case 'r':
        if(computadora == 'r'){
            cout<<"Empate!\n";
        }
        else if(computadora == 'p'){
            cout<<"Perdiste!...\n";
        }else{
            cout<<"Ganaste!..\n";
        }
        break;
    case 'p':
        if(computadora == 'p'){
            cout<<"Empate!\n";
        }
        else if(computadora == 't'){
            cout<<"Perdiste!...\n";
        }else{
            cout<<"Ganaste!..\n";
        }
        break;
    case 't':
        if(computadora == 't'){
            cout<<"Empate!\n";
        }
        else if(computadora == 'p'){
            cout<<"Perdiste!...\n";
        }else{
            cout<<"Ganaste!..\n";
        }
        break;
    }
}