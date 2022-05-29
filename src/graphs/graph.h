#include <stdint.h>
#include "../collections/list.h"

/* Grafo simples definido por lista de adjacências. */
typedef List *GraphList[];

/* Grafo simples definido por matriz de adjacências. */
typedef uint32_t GraphMatrix[][];
