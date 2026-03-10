#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ===============================
// Constantes globales
// ===============================
#define MAX_NUMEROS 1000   // Límite superior para la cantidad de números

// ===============================
// Declaración de funciones
// ===============================
void limpiarPantalla(void);
void pausar(void);
void mostrarMenuPrincipal(void);
void ejecutarAnalisisNumerico(void);
int leerEntero(const char *mensaje, int min, int max);

// ===============================
// Función principal
// ===============================
int main(void) {
    int opcion;

    do {
        limpiarPantalla();
        mostrarMenuPrincipal();

        // Leer opción con validación
        opcion = leerEntero("\nSeleccione una opción: ", 1, 2);

        switch (opcion) {
            case 1:
                ejecutarAnalisisNumerico();
                break;
            case 2:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                // No debería ocurrir, ya que leerEntero valida
                printf("Opción no válida.\n");
                pausar();
                break;
        }

    } while (opcion != 2);

    return 0;
}

// ===============================
// Limpia la pantalla (compatible Linux / Windows)
// ===============================
void limpiarPantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ===============================
// Pausa la ejecución hasta presionar ENTER
// ===============================
void pausar(void) {
    printf("\nPresione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer
    getchar(); // esperar ENTER
}

// ===============================
// Muestra el menú principal
// ===============================
void mostrarMenuPrincipal(void) {
    printf("=== ANALISIS NUMÉRICO AVANZADO ===\n");
    printf("1. Ingresar y analizar números\n");
    printf("2. Salir\n");
}

// ===============================
// Lee un entero con validación (repite hasta que sea válido)
// ===============================
// - mensaje: lo que se muestra al usuario
// - min / max: valores permitidos (pueden ser iguales si no hay restricción)
int leerEntero(const char *mensaje, int min, int max) {
    char buffer[100];
    char *endptr;
    long valor;
    int valido = 0;

    do {
        printf("%s", mensaje);

        // Leer línea completa
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer la entrada. Intente nuevamente.\n");
            continue;
        }

        // Eliminar salto de línea final, si existe
        buffer[strcspn(buffer, "\n")] = '\0';

        // Intentar convertir a número
        valor = strtol(buffer, &endptr, 10);

        // Validar que toda la cadena sea un número (sin basura después)
        if (*endptr != '\0') {
            printf("Entrada inválida. Debe ingresar un número entero.\n");
            continue;
        }

        // Validar rango si aplica
        if (valor < min || valor > max) {
            printf("Valor fuera de rango (%d - %d). Intente nuevamente.\n", min, max);
            continue;
        }

        valido = 1;

    } while (!valido);

    return (int)valor;
}
// ===============================
// Ejecuta el análisis numérico completo
// ===============================
void ejecutarAnalisisNumerico(void) {
    int cantidadNumeros;
    int numeroActual;
    int pares = 0, impares = 0;
    int positivos = 0, negativos = 0, nulos = 0;
    int maximo = INT_MIN;
    int minimo = INT_MAX;
    float sumaPositivos = 0.0f;
    float sumaNegativos = 0.0f;

    limpiarPantalla();
    printf("=== INGRESO DE DATOS ===\n");

    // Leer cantidad de números a analizar
    cantidadNumeros = leerEntero(
        "Ingrese la cantidad de números a analizar (1 - 1000): ",
        1, MAX_NUMEROS
    );

    // Bucle para ingresar y analizar N números
    for (int i = 0; i < cantidadNumeros; i++) {
        char mensaje[50];
        snprintf(mensaje, sizeof(mensaje), "Número %d: ", i + 1);
        numeroActual = leerEntero(mensaje, INT_MIN, INT_MAX);

        // Determinar par o impar
        if (numeroActual % 2 == 0)
            pares++;
        else
            impares++;

        // Clasificar positivo, negativo o nulo
        if (numeroActual > 0) {
            positivos++;
            sumaPositivos += numeroActual;
        } else if (numeroActual < 0) {
            negativos++;
            sumaNegativos += numeroActual;
        } else {
            nulos++;
        }

        // Actualizar máximos y mínimos
        if (numeroActual > maximo) maximo = numeroActual;
        if (numeroActual < minimo) minimo = numeroActual;
    }

    // Calcular promedios
    float promedioPositivos = (positivos > 0) ? (sumaPositivos / positivos) : 0.0f;
    float promedioNegativos = (negativos > 0) ? (sumaNegativos / negativos) : 0.0f;

    // Mostrar resultados
    limpiarPantalla();
    printf("=== RESULTADOS DEL ANÁLISIS ===\n");
    printf("Cantidad de pares: %d\n", pares);
    printf("Cantidad de impares: %d\n", impares);
    printf("Cantidad de positivos: %d\n", positivos);
    printf("Cantidad de negativos: %d\n", negativos);
    printf("Cantidad de nulos (0): %d\n", nulos);
    printf("Promedio de positivos: %.2f\n", promedioPositivos);
    printf("Promedio de negativos: %.2f\n", promedioNegativos);
    printf("Valor máximo: %d\n", maximo);
    printf("Valor mínimo: %d\n", minimo);

    pausar();
}
