#include <stdint.h>

#define OK 1
#define NOT_OK 0
#define NULL_ERROR 2
#define INVALID_INDEX_ERROR 3

/* Heap Estática (definida por array de tamanho definido) Genérica
(utiliza ponteiros do tipo void). */
typedef struct heap Heap;

/* ----------------------------------------- Protótipos ----------------------------------------- */

/* Cria uma nova heap vazia.
Em caso de erro de alocação, retorna `NULL`. */
Heap *new_heap(uint8_t max_size);

/* Limpa a heap da memória. */
void free_heap(Heap *heap);

/* Cria uma nova heap à partir de um "dicionário" (dois arrays de mesmo tamanho vinculados pela
relação respectiva de cada índice). Note que, se `size > max_size` então `max_size` valores serão
passados para a heap. Em caso de erro de alocação, retorna `NULL`. */
Heap *new_heap_from(void *data[], uint32_t priorities[], uint8_t size, uint8_t max_size);

/* Insere um novo elemento na heap, com base na prioridade do mesmo.
Erros: `NULL_ERROR`, `NOT_OK` (atingido o limite máximo da heap), `OK`. */
uint8_t heap_insert(Heap *, void *data, uint32_t priority);

/* Remove o elemento de maior prioridade na heap.
Erros: `NULL_ERROR`, `NOT_OK` (se a heap estiver vazia), `OK`. */
uint8_t heap_remove(Heap *);

/* Remove e retorna o elemento de maior prioridade na Heap.
Erros: `NULL_ERROR`, `NOT_OK` (se a heap estiver vazia), `OK`. */
uint8_t heap_pop(Heap *, void **data);

/* Acessa o elemento de maior prioridade na Heap (sem removê-lo).
Erros: `NULL_ERROR`, `NOT_OK` (se a heap estiver vazia), `OK`. */
uint8_t heap_get(Heap *heap, void **out);

/* Altera a prioridade de um elemento na heap. Mantendo as regras de posicionamento da mesma.
Erros: `NULL_ERROR`, `NOT_OK`, `OK`. */
uint8_t heap_change_priority(Heap *, uint8_t, uint32_t);

/* Faz a ordenação em ordem crescente de um vetor com base na heap, e usando os dados da mesma. */
// uint8_t heap_sort(Heap *heap, struct data *([]));
// WATCH
uint8_t heap_sort(Heap *heap, void *(*data[]));

// Métodos extras.

void print_heap(Heap *heap);
