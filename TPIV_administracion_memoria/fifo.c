#include <stdio.h>
#include <stdlib.h>

#define MARCOS 4   // Número de marcos de página
#define MAX_REFERENCIAS 1000  // Tamaño máximo esperado del archivo CSV

int main() {
    FILE *archivo;
    int referencias[MAX_REFERENCIAS];
    int memoria[MARCOS];
    int num_referencias = 0;
    int fallos_pagina = 0;
    int i, j, encontrado;

    // Inicializar memoria vacía
    for (i = 0; i < MARCOS; i++) {
        memoria[i] = -1;
    }

    // Abrir el archivo CSV
    archivo = fopen("datos.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Leer los valores del CSV separados por comas
    while (fscanf(archivo, "%d,", &referencias[num_referencias]) == 1) {
        num_referencias++;
    }

    fclose(archivo);

    // Procesar las referencias
    for (i = 0; i < num_referencias; i++) {
        int ref = referencias[i];
        encontrado = 0;

        // Verificar si la referencia ya está en memoria
        for (j = 0; j < MARCOS; j++) {
            if (memoria[j] == ref) {
                encontrado = 1;
                break;
            }
        }

        // Si no se encontró, es un fallo de página
        if (!encontrado) {
            fallos_pagina++;
            // Buscar una posición vacía
            int pos_vacia = -1;
            for (j = 0; j < MARCOS; j++) {
                if (memoria[j] == -1) {
                    pos_vacia = j;
                    break;
                }
            }

            if (pos_vacia != -1) {
                memoria[pos_vacia] = ref;  // Agregar en espacio vacío
            } else {
                // Si no hay espacio, eliminar el más antiguo (FIFO)
                for (j = 0; j < MARCOS - 1; j++) {
                    memoria[j] = memoria[j + 1];
                }
                memoria[MARCOS - 1] = ref;
            }
        }
    }

    printf("Total de fallos de página: %d\n", fallos_pagina);

    return 0;
}
