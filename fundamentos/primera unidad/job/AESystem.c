#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ESTUDIANTES 100
#define NUM_NOTAS 3

/* Función auxiliar para limpiar el búfer de entrada hasta el '\n' o EOF */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartamos caracteres hasta fin de línea */
    }
}

int main(void) {
    int numEstudiantes;
    char nombres[MAX_ESTUDIANTES][50];
    float notas[MAX_ESTUDIANTES][NUM_NOTAS];
    float promedios[MAX_ESTUDIANTES];

    float promedioGeneral = 0.0f;
    float notaMaxima = 0.0f;
    float notaMinima = 20.0f;
    int cantidadAprobados = 0;
    int cantidadDesaprobados = 0;

    /* Limpiar pantalla al inicio (Linux) */
    system("clear");

    printf("=== REGISTRO DE NOTAS UNIVERSITARIAS ===\n\n");

    /* Solicitar cantidad de estudiantes (validada) */
    do {
        printf("Ingrese la cantidad de estudiantes (max %d): ", MAX_ESTUDIANTES);
        if (scanf("%d", &numEstudiantes) != 1) {
            /* Si la entrada no es un entero válido, limpiamos y pedimos de nuevo */
            printf("Entrada inválida. Intente nuevamente.\n");
            clear_input_buffer();
            numEstudiantes = 0;
            continue;
        }
        if (numEstudiantes <= 0 || numEstudiantes > MAX_ESTUDIANTES) {
            printf("Cantidad no válida. Intente nuevamente.\n");
        }
    } while (numEstudiantes <= 0 || numEstudiantes > MAX_ESTUDIANTES);

    /* Consumir el '\n' que quedó después de leer el entero */
    clear_input_buffer();

    /* Ingreso de datos por estudiante */
    for (int i = 0; i < numEstudiantes; i++) {
        printf("\n--- Estudiante %d ---\n", i + 1);

        /* Leer el nombre con fgets (seguro y permite espacios) */
        printf("Nombre: ");
        if (fgets(nombres[i], sizeof(nombres[i]), stdin) == NULL) {
            /* si hay un error de entrada, ponemos nombre vacío */
            nombres[i][0] = '\0';
        } else {
            /* eliminar el salto de línea final si existe */
            size_t len = strlen(nombres[i]);
            if (len > 0 && nombres[i][len - 1] == '\n') {
                nombres[i][len - 1] = '\0';
            }
        }

        /* Leer las 3 notas con validación */
        for (int j = 0; j < NUM_NOTAS; j++) {
            int ok;
            do {
                printf("Ingrese nota %d (0-20): ", j + 1);
                ok = scanf("%f", &notas[i][j]);
                if (ok != 1) {
                    /* entrada inválida (no es float) */
                    printf("Entrada invalida. Introduzca un numero (ej: 12.5).\n");
                    clear_input_buffer();
                    continue;
                }
                if (notas[i][j] < 0.0f || notas[i][j] > 20.0f) {
                    printf("Nota inválida. Debe estar entre 0 y 20.\n");
                    ok = 0; /* fuerza repetir */
                }
            } while (!ok);
            /* luego de leer un número, dejamos el '\n' pendiente:
               lo consumiremos antes de la siguiente lectura de nombre
               (o al inicio de la próxima iteración) */
        }

        /* Consumir el resto de la línea (el '\n' luego del último scanf) para
           evitar que el siguiente fgets lea una línea vacía. */
        clear_input_buffer();
    }

    /* Cálculos: promedios individuales y estadísticas globales */
    for (int i = 0; i < numEstudiantes; i++) {
        float sumaNotas = 0.0f;
        for (int j = 0; j < NUM_NOTAS; j++) {
            sumaNotas += notas[i][j];
            if (notas[i][j] > notaMaxima) notaMaxima = notas[i][j];
            if (notas[i][j] < notaMinima) notaMinima = notas[i][j];
        }
        promedios[i] = sumaNotas / NUM_NOTAS;
        promedioGeneral += promedios[i];
        if (promedios[i] >= 11.0f) cantidadAprobados++;
        else cantidadDesaprobados++;
    }

    promedioGeneral /= numEstudiantes;

    /* Limpiar pantalla antes de mostrar resultados */
    system("clear");

    /* Mostrar resultados individuales */
    printf("=== RESULTADOS INDIVIDUALES ===\n");
    for (int i = 0; i < numEstudiantes; i++) {
        printf("\nEstudiante: %s\n", nombres[i]);
        printf("Notas: ");
        for (int j = 0; j < NUM_NOTAS; j++) {
            printf("%.2f ", notas[i][j]);
        }
        printf("\nPromedio: %.2f - Estado: %s\n",
               promedios[i],
               (promedios[i] >= 11.0f) ? "Aprobado" : "Desaprobado");
    }

    /* Estadísticas generales */
    printf("\n=== ESTADÍSTICAS GENERALES ===\n");
    printf("Promedio general del curso: %.2f\n", promedioGeneral);
    printf("Nota máxima global: %.2f\n", notaMaxima);
    printf("Nota mínima global: %.2f\n", notaMinima);
    printf("Cantidad de aprobados: %d\n", cantidadAprobados);
    printf("Cantidad de desaprobados: %d\n", cantidadDesaprobados);

    printf("\nPrograma finalizado correctamente\n");
    return 0;
}
