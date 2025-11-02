Algoritmo FIFO (First In, First Out)

El algoritmo FIFO reemplaza las páginas en el mismo orden en que llegaron a la memoria.
Cuando ocurre un fallo de página, la página más antigua (la que entró primero) se elimina para dejar espacio a la nueva.

Pasos:

1. Leer la secuencia de referencias desde un archivo CSV.
2. Verificar si la página está ya en memoria:
    Si está → no hay fallo de página.
    Si no está → fallo de página.
3. Si la memoria tiene espacio, se agrega la nueva página.
4. Si la memoria está llena, se elimina la página más antigua (la primera en entrar).
5. Al final, se muestra el número total de fallos de página.

Algoritmo LRU (Least Recently Used)

El algoritmo LRU reemplaza la página menos recientemente utilizada.
Cada vez que se accede a una página, se marca como la más reciente. Si ocurre un fallo, se elimina la menos reciente.

Pasos:

1. Leer las referencias desde el archivo CSV.
2. Comprobar si la página está en memoria:
    Si está → se mueve al final de la lista (la más recientemente usada).
    Si no está → se registra un fallo.
4. Si la memoria está llena, se elimina la menos recientemente usada (posición inicial).
5. Se cuenta el total de fallos de página al finalizar la ejecución.

| Caso | Entradas (datos.csv)      | N° de marcos | Resultado esperado               |
| ---- | ------------------------- | ------------ | -------------------------------- |
| 1    | `1,2,3,4,1,2,5,1,2,3,4,5` | 4            | FIFO: 10 fallos / LRU: 8 fallos  |
| 2    | `7,0,1,2,0,3,0,4,2,3,0,3` | 3            | FIFO: 9 fallos / LRU: 8 fallos   |
| 3    | `1,2,3,4,5,1,2,3,4,5`     | 3            | FIFO: 10 fallos / LRU: 10 fallos |
| 4    | `1,2,3,4,1,2,5,1,2,3,4,5` | 5            | FIFO: 8 fallos / LRU: 7 fallos   |

Entorno de desarrollo

Este apartado debe permitir que cualquier persona pueda reproducir la ejecución del programa correctamente.

Sistema operativo: Linux Mint 21.3 Virginia

Compilador: gcc 11.4.0

Editor o IDE: Visual Studio Code

Comando de compilación:

gcc fifo.c -o fifo
gcc lru.c -o lru


Comando de ejecución:

./fifo
./lru

Dependencias:

FIFO: `<stdio.h>`, `<stdlib.h>` para entrada/salida y manejo básico de memoria

LRU: `<stdio.h>`, `<stdlib.h>`, `<string.h>` para uso de `strtok()` para procesar CSV 

