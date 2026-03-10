#include <iostream>
#include <string>

using namespace std;

class AccesSistem
{
public:
    // Método principal de acceso
    bool login() {
        while (contador <= MAX_INTENTOS) {
            // Si usuario es incorrecto, pedir ambos datos
            if (user.empty() || !validarUsuario(user)) {
                user = datosUsuario("usuario");
                if(validarUsuario)
                pass = datosUsuario("contraseña");
            }
            // Si usuario es correcto, pero pass incorrecto
            else if (!validarPassword(pass)) {
                pass = datosUsuario("contraseña");
            }

            // Validamos credenciales
            if (validarAcceso(user, pass)) {
                cout << "\nAcceso concedido.\n";
                return true;
            } else {
                controlIntentos();
            }
        }

        cout << "Acceso denegado. Ha superado el número máximo de intentos.\n";
        return false;
    }

private:
    string user, pass;
    int contador = 1;
    const int MAX_INTENTOS = 3;

    // Solicita un dato al usuario
    string datosUsuario(const string& tipo) {
        string dato;
        cout << "Ingrese " << tipo << ": ";
        cin >> dato;
        return dato;
    }

    // Verifica si usuario es correcto
    bool validarUsuario(const string& u) {
        return (u == "admin");
    }

    // Verifica si contraseña es correcta
    bool validarPassword(const string& p) {
        return (p == "1234");
    }

    // Valida ambos datos
    bool validarAcceso(const string& u, const string& p) {
        return (validarUsuario(u) && validarPassword(p));
    }

    // Controla los intentos y mensajes
    void controlIntentos() {
        cout << "\nCredenciales incorrectas.\n";

        if (user != "admin" && pass != "1234") {
            cout << "Usuario y contraseña incorrectos.\n";
            user.clear();
            pass.clear();
        } else if (user == "admin" && pass != "1234") {
            cout << "Contraseña incorrecta.\n";
            pass.clear();
        } else if (user != "admin" && pass == "1234") {
            cout << "Usuario incorrecto.\n";
            user.clear();
            pass.clear();
        }

        cout << "Intento " << contador << " de " << MAX_INTENTOS << "\n\n";
        contador++;
    }
};

int main() {
    //instanciar objeto 
    AccesSistem a;
    a.login();
    return 0;
}