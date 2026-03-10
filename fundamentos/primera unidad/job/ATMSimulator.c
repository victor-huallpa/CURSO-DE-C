#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===============================
// Constantes globales
// ===============================
#define PIN_INICIAL 1234        // PIN por defecto
#define MAX_INTENTOS 3          // Número máximo de intentos para ingresar PIN

// ===============================
// Variables globales
// ===============================
float saldoCuenta = 1000.00f;   // Saldo inicial de la cuenta
int pinActual = PIN_INICIAL;    // PIN que se podrá cambiar

// ===============================
// Declaración de funciones
// ===============================
void limpiarPantalla(void);
void pausar(void);
int validarPin(void);
void mostrarMenu(void);
void consultarSaldo(void);
void depositarDinero(void);
void retirarDinero(void);
void cambiarPin(void);

// ===============================
// Función principal
// ===============================
int main(void) {
    int opcion;

    limpiarPantalla();
    printf("=== SIMULADOR DE CAJERO AUTOMATICO ===\n");

    // Validar PIN al inicio con límite de intentos
    if (!validarPin()) {
        printf("\nSe ha excedido el número de intentos. Acceso bloqueado.\n");
        return 0;
    }

    // Bucle principal del menú
    do {
        mostrarMenu();
        printf("\nSeleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            // Manejo de entrada inválida
            printf("Entrada inválida. Intente nuevamente.\n");
            // Limpiar buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (opcion) {
            case 1:
                consultarSaldo();
                break;
            case 2:
                depositarDinero();
                break;
            case 3:
                retirarDinero();
                break;
            case 4:
                cambiarPin();
                break;
            case 5:
                printf("\nGracias por usar el cajero. ¡Hasta pronto!\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 5);

    return 0;
}

// ===============================
// Definición de funciones auxiliares
// ===============================

// Limpia la pantalla (compatible Linux / Windows)
void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausa la ejecución hasta presionar ENTER
void pausar(void) {
    printf("\nPresione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer
    getchar(); // esperar ENTER
}

// Valida el PIN de acceso inicial
int validarPin(void) {
    int pinIngresado;
    int intentos = 0;

    do {
        printf("\nIngrese su PIN de seguridad: ");
        if (scanf("%d", &pinIngresado) != 1) {
            // Entrada no numérica
            printf("Entrada inválida. Intente nuevamente.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (pinIngresado == pinActual) {
            printf("\nPIN correcto. Acceso concedido.\n");
            return 1;
        } else {
            intentos++;
            printf("PIN incorrecto. Intento %d de %d\n", intentos, MAX_INTENTOS);
        }

    } while (intentos < MAX_INTENTOS);

    return 0; // Acceso denegado
}

// Muestra el menú principal
void mostrarMenu(void) {
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Cambiar PIN de seguridad\n");
    printf("5. Salir\n");
}

// Consultar saldo actual
void consultarSaldo(void) {
    printf("\nSu saldo actual es: S/. %.2f\n", saldoCuenta);
    pausar();
}

// Depositar dinero a la cuenta
void depositarDinero(void) {
    float monto;
    printf("\nIngrese el monto a depositar: ");
    if (scanf("%f", &monto) != 1) {
        printf("Entrada inválida. Depósito cancelado.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (monto <= 0) {
        printf("Monto inválido. Debe ser mayor a 0.\n");
    } else {
        saldoCuenta += monto;
        printf("Depósito realizado. Nuevo saldo: S/. %.2f\n", saldoCuenta);
    }
    pausar();
}

// Retirar dinero de la cuenta
void retirarDinero(void) {
    float monto;
    printf("\nIngrese el monto a retirar: ");
    if (scanf("%f", &monto) != 1) {
        printf("Entrada inválida. Operación cancelada.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (monto <= 0) {
        printf("Monto inválido. Debe ser mayor a 0.\n");
    } else if (monto > saldoCuenta) {
        printf("Fondos insuficientes. Su saldo es: S/. %.2f\n", saldoCuenta);
    } else {
        saldoCuenta -= monto;
        printf("Retiro exitoso. Nuevo saldo: S/. %.2f\n", saldoCuenta);
    }
    pausar();
}

// Cambiar el PIN actual
void cambiarPin(void) {
    int pinAntiguo, pinNuevo, pinConfirmacion;

    printf("\nIngrese su PIN actual: ");
    if (scanf("%d", &pinAntiguo) != 1) {
        printf("Entrada inválida. Operación cancelada.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (pinAntiguo != pinActual) {
        printf("PIN incorrecto. No se puede cambiar.\n");
        pausar();
        return;
    }

    printf("Ingrese su nuevo PIN: ");
    if (scanf("%d", &pinNuevo) != 1) {
        printf("Entrada inválida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Confirme su nuevo PIN: ");
    if (scanf("%d", &pinConfirmacion) != 1) {
        printf("Entrada inválida.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (pinNuevo != pinConfirmacion) {
        printf("Los PIN no coinciden. Intente nuevamente.\n");
    } else {
        pinActual = pinNuevo;
        printf("PIN cambiado exitosamente.\n");
    }

    pausar();
}
