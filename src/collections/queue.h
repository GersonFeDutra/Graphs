// Flags de erros.
#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Lista inexistente. */
#define EMPTY_ERROR -2 /* Lista vazia. */
#define NAME_MAX_SIZE 50

// Fila Dinâmica Homogênea Genérica (recebe um ponteiro do tipo `void`).
typedef struct queue Queue;

/* ----------------------------------------- Protótipos ----------------------------------------- */

/* Cria uma fila vazia. */
Queue *new_queue();
/* `Queue` é um nó descritor `struct queue` que armazena dados de acesso aos elementos da fila
(o elemento inicial e o elemento final). */

/* 'Destrói' uma fila, esvaziando seu conteúdo. */
void empty_queue(Queue *);

/* Destrói uma fila, eliminando-a da memória. */
int free_queue(Queue **);

/* Retorna a quantidade de elementos da fila.
Se a fila não existir retorna `NULL_ERROR`, ao invés disso. */
int queue_size();

/* Insere um elemento. Note que, filas só podem inserir no final.
Retorno: NULL_ERROR, NOT_OK, OK. */
int add_to_queue(Queue *, void *);

/* Remove um elemento. Note que, filas só podem remover do início.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int remove_from_queue(Queue *);

/* Acessa um elemento, sendo esse o primeiro elemento da fila.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int queue_get(Queue *, void **);

/* Inverte a direção da fila, isto é, o primeiro vira o último e o último o primeiro.
Retorno: NULL_ERROR, OK. */
int invert_queue(Queue *);

/* Dado duas Filas A (`to`) e B (`from`), transfere todos elementos de B para A
- esvaziando o conteúdo de B.
Retorno: NULL_ERROR, OK.*/
int migrate_queue(Queue *to, Queue *from);
