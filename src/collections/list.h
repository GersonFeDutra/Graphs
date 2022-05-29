#include <stdbool.h>
#include <stdint.h>

#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Lista inexistente. */
#define EMPTY_ERROR -2 /* Lista vazia. */

// Lista Dinâmica Simplesmente Encadeada Homogênea Genérica (usa ponteiro do tipo void).
typedef struct node *List;
/* Usamos `typedef` para definir o tipo de dado e ocultar o `*` da lista */

/* Recebe uma função que retorna um Boolean de comparação entre os elementos passados. */
typedef int (*compare_func)(void *, void *);


/* ----------------------------------------- Protótipos ----------------------------------------- */

/* Cria uma lista vazia. */
List *new_list(void);
/* 'List` é um `struct node *` que passaremos por referência: `List *`; isto é, `struct node
**`. Isso permite que o ponteiro inicial da lista seja alterado internamente nas funções. */

/* 'Destrói' uma lista, esvaziando o seu conteúdo. */
void empty_list(List *);

// ------------------- Funções de inserção

/* Insere um elemento no início da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int list_add_at_start(List *, void *);

/* Insere um elemento no final da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int list_add_at_end(List *list, void *);

/* Insere um elemento de forma 'ordenada', relativo à posição dos elementos na lista.
Retorno: NULL_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_add_at(List *list, void *, uint8_t index);

// ------------------- Funções de remoção

/* Remove o elemento indicado da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int list_remove(List *, void *, compare_func);

/* Remove o primeiro elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK */
int list_remove_from_start(List *list);

/* Remove o último elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int list_remove_from_end(List *list);

/* Remove um elemento de acordo com sua posição na lista.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_remove_from(List *list, uint8_t index);

// ------------------- Funções de acesso

/* Acessa um elemento da matriz com busca.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int list_get(List *list, void *, void **output, compare_func);

/* Acessa um elemento da lista por índice.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_get_from(List *list, uint8_t index, void **output);

// ------------------- Funções extras

/* Retorna `OK` se a lista estiver vazia, e `NOT_OK`, caso contrário.
Também retorna `NULL_ERROR`, se a lista for inexistente */
int is_list_empty(List *list);

// Por ser uma lista dinâmica ela não pode ficar cheia.
/* //Desnecessário
int is_list_full(List *list)
{
    return NOT_OK;
}
*/

/* Retorna a quantidade de elementos da lista. (Calcula a cada chamada).
Se a lista não existir retorna `NULL_ERROR`, ao invés disso. */
int list_size(List *list);

/* Indica se a peça determinada existe na lista. - Retorno Boolean.
Se a lista não existir retorna `NULL_ERROR`, ao invés disso. */
int list_has(List *, void *, compare_func);

/* Retorna a quantidade de peças do tipo indicado existentes na lista.
Se a lista não existir retorna `NULL_ERROR`, ao invés disso. */
int list_count(List *, void *, compare_func);
