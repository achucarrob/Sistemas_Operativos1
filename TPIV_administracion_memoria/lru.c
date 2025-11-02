#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MARCOS 4                 // Capacidad de la cache (nº de marcos)
#define MAX_REFERENCIAS 100000   // Máximo de referencias a leer
#define LINEA_MAX 4096           // Tamaño de buffer para leer líneas del CSV

// Mueve el elemento en índice idx al final (MRU), desplazando el resto a la izquierda
static void mover_a_mru(int *mem, int len, int idx) {
    int pagina = mem[idx];
    for (int i = idx; i < len - 1; i++) {
        mem[i] = mem[i + 1];
    }
    mem[len - 1] = pagina;
}

// Acceder a una página con política LRU.
// mem: arreglo que mantiene el orden LRU..MRU
// len: cantidad actual de páginas en memoria (<= cap)
// cap: capacidad total (MARCOS)
// pagina: referencia solicitada
// Retorna 1 si hubo fallo de página, 0 si hit (sin fallo).
static int lru_acceder(int *mem, int *len, int cap, int pagina) {
    // Buscar si está en memoria (hit)
    for (int i = 0; i < *len; i++) {
        if (mem[i] == pagina) {
            // Mover a MRU (al final)
            mover_a_mru(mem, *len, i);
            return 0; // hit -> no hay fallo
        }
    }

    // Miss: hay fallo de página
    if (*len < cap) {
        // Aún hay espacio: añadir al final (MRU)
        mem[*len] = pagina;
        (*len)++;
    } else {
        // Sin espacio: expulsar LRU (posición 0) y añadir como MRU
        for (int i = 0; i < cap - 1; i++) {
            mem[i] = mem[i + 1];
        }
        mem[cap - 1] = pagina;
    }
    return 1; // hubo fallo
}

int main(void) {
    FILE *archivo = fopen("datos.csv", "r");
    if (!archivo) {
        fprintf(stderr, "Error al abrir 'datos.csv'\n");
        return 1;
    }

    int referencias[MAX_REFERENCIAS];
    int num_referencias = 0;

    // Leer CSV: admite comas, punto y coma y saltos de línea como separadores
    char linea[LINEA_MAX];
    while (fgets(linea, sizeof(linea), archivo)) {
        char *token = strtok(linea, ",;\n\r\t ");
        while (token) {
            if (num_referencias >= MAX_REFERENCIAS) {
                fprintf(stderr, "Se excedió MAX_REFERENCIAS (%d)\n", MAX_REFERENCIAS);
                fclose(archivo);
                return 1;
            }
            referencias[num_referencias++] = atoi(token);
            token = strtok(NULL, ",;\n\r\t ");
        }
    }
    fclose(archivo);

    int memoria[MARCOS];
    int len_mem = 0;         // cantidad actual en memoria
    int fallos_pagina = 0;

    // Procesamiento de referencias aplicando LRU
    for (int i = 0; i < num_referencias; i++) {
        fallos_pagina += lru_acceder(memoria, &len_mem, MARCOS, referencias[i]);
    }

    printf("Total de fallos de página: %d\n", fallos_pagina);
    return 0;
}
