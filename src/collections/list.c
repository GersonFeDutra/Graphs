#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//#define MALLOC_ERROR {WARNING("Memória insuficiente!"); return NOT_OK;}
#define CHECK_LIST(LIST)                                                                           \
	if (LIST == NULL)                                                                              \
		return NULL_ERROR;                                                                         \
	if (*LIST == NULL)                                                                             \
		return EMPTY_ERROR;

/* Um elemento único da lista. */
struct node {
	void *element;
	struct node *next;
};

/* Representação do `struct node` (um elemento único da lista). */
typedef struct node Node;

/* Nota: `List *` representa as seguintes opções:
- struct node **
- Node **
*/

List *new_list()
{
	List *list = (List *)malloc(sizeof(List));

	if (list != NULL)
		*list = NULL;

	return list;
}


void empty_list(List *list)
{
	if (list == NULL)
		return;

	Node *aux;

	while (*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	}
	// free(l); // Opcional: limpa também o ponteiro inicial, não só os elementos.
}


int list_size(List *list)
{
	if (list == NULL)
		return NULL_ERROR;

	if (*list == NULL)
		return 0;

	int value = 0;
	Node *aux = *list;

	while (aux != NULL) {
		aux = aux->next;
		value++;
	}

	return value;
}


int list_has(List *list, void *element, compare_func eq)
{
	if (list == NULL)
		return NULL_ERROR;

	Node *aux = *list;

	while (aux != NULL)

		if ((*eq)(aux->element, element))
			return true;
		else
			aux = aux->next;

	return false;
}


int list_count(List *list, void *element, compare_func eq)
{
	if (list == NULL)
		return NULL_ERROR;

	if (*list == NULL)
		return 0;

	int value = 0;
	Node *aux = *list;

	while (aux != NULL) {

		if ((*eq)(element, aux->element))
			value++;

		aux = aux->next;
	}

	return value;
}


int is_list_empty(List *list)
{
	if (list == NULL)
		return NULL_ERROR;

	if (*list == NULL)
		return OK;

	return NOT_OK;
}


int list_add_at_start(List *list, void *new_element)
{
	if (list == NULL)
		return NULL_ERROR;

	Node *new = (Node *)malloc(sizeof(Node));

	if (new == NULL)
		return NOT_OK;

	new->element = new_element;
	new->next = *list;
	*list = new;

	return OK;
}


int list_add_at_end(List *list, void *new_element)
{
	if (list == NULL)
		return NULL_ERROR;

	Node *new = (Node *)malloc(sizeof(Node));

	if (new == NULL)
		return NOT_OK;

	new->element = new_element;
	new->next = NULL;

	if (*list == NULL) {
		*list = new;
	}
	else {
		Node *aux = *list;

		while (aux->next != NULL)
			aux = aux->next;

		aux->next = new;
	}

	return OK;
}


int list_add_at(List *list, void *new_element, uint8_t index)
{
	if (list == NULL)
		return NULL_ERROR;

	if (index == 0) {
		Node *new = (Node *)malloc(sizeof(Node));

		if (new == NULL)
			return NOT_OK;
		;

		new->next = *list;
		new->element = new_element;
		*list = new;

		return OK;
	}

	if (*list == NULL)
		return NOT_OK;

	uint8_t i = 1;
	Node *previous = *list;
	// Para igualar a verificação com o 'próximo do anterior' iniciamos a contagem pelo i(0) + 1.
	// Usamos o 'próximo do anterior' pois, como devemos inserir um elemento na posição do índice,
	// isso evita armazenar um auxiliar adicional.
	while (previous->next != NULL && i != index) {
		previous = previous->next;
		++i;
	}

	if (previous->next == NULL)
		return NOT_OK;

	Node *new = (Node *)malloc(sizeof(Node));

	if (new == NULL)
		return NOT_OK;

	new->next = previous->next;
	new->element = new_element;
	previous->next = new;

	return OK;
}


int list_remove(List *list, void *element, compare_func eq)
{
	CHECK_LIST(list)
	Node *previous = *list; // Começa como o primeiro elemento da lista.
	// Começa como o segundo elemento da lista, possivelmente NULL.
	Node *current = previous->next;

	if ((*eq)(previous->element, element))
		*list = current;

	else if (current == NULL)
		return NOT_OK;

	else {
		while (!(*eq)(current->element, element) && current->next != NULL) {
			previous = current;
			current = current->next;
		}

		if (current->next == NULL && !(*eq)(current->element, element))
			return NOT_OK;

		previous->next = current->next;
		free(current);
	}

	return OK;
}


int list_remove_from_start(List *list)
{
	CHECK_LIST(list)
	Node *aux = *list;
	*list = aux->next;
	free(aux);

	return OK;
}


int list_remove_from_end(List *list)
{
	CHECK_LIST(list)
	Node *previous = *list; // Começa como o primeiro elemento da lista.
	// Começa como o segundo elemento da lista, possivelmente `NULL`.
	Node *current = previous->next;

	if (current == NULL) {
		free(previous);
		*list = NULL;
	}
	else if (current->next == NULL) {
		// Fiz esse `esse if` adicional para evitar ficar dando cache em `previous` e `current` ao
		// mesmo tempo durante a iteração do loop abaixo.
		free(current);
		previous->next = NULL;
	}
	else {
		while (current->next->next != NULL)
			current = current->next;

		previous = current;
		current = current->next;
		previous->next = current->next; // Equivalente à `... = NULL`.
		free(current);
	}

	return OK;
}


int list_remove_from(List *list, uint8_t index)
{
	CHECK_LIST(list)

	Node *aux;

	if (index == 0) {
		aux = (*list)->next;
		free(*list);
		*list = aux;

		return OK;
	}

	uint8_t i = 1;
	Node *previous = *list;
	// Para igualar a verificação com o 'próximo do anterior' iniciamos a contagem pelo i(0) + 1.
	// Usamos o 'próximo do anterior' pois, como devemos inserir um elemento na posição do índice,
	// isso evita armazenar um auxiliar adicional.
	while (previous->next != NULL && i != index) {
		previous = previous->next;
		++i;
	}

	if (previous->next == NULL)
		return NOT_OK;

	aux = previous->next->next;
	free(previous->next);
	previous->next = aux;

	return OK;
}


int list_get(List *list, void *element, void **output, compare_func eq)
{
	CHECK_LIST(list)
	Node *aux = *list;

	while (aux != NULL && !(*eq)(element, aux->element))
		aux = aux->next;

	if (aux == NULL)
		return NOT_OK;

	*output = aux->element;

	return OK;
}


int list_get_from(List *list, uint8_t index, void **output)
{
	CHECK_LIST(list);

	uint8_t i = 0;
	Node *aux = *list;

	while (aux != NULL && i != index) {
		aux = aux->next;
		++i;
	}

	if (aux == NULL)
		return NOT_OK;

	*output = aux->element;

	return OK;
}
