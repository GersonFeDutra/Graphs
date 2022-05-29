#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_QUEUE(QUEUE)                                                                         \
	if (QUEUE == NULL)                                                                             \
		return NULL_ERROR;                                                                         \
	if (QUEUE->start == NULL)                                                                      \
		return EMPTY_ERROR;

// Nó descritor.
struct queue {
	struct element *start;
	struct element *end;
	/* Dentro do nó descritor podemos ter qualquer informação sobre o nosso TAD, além das
	informações essenciais dessa estrutura (que nesse caso são `start` e `end`): */
	// Embora `size` não seja uma informação essencial pode ser útil fora do TAD.
	int size; // A quantidade de elementos da fila.
	/* A desvantagem desses dados adicionais é que eles devem ser constantemente sincronizados
	conforme os dados do TAD vão sendo modificados. */
};

// Elemento individual.
struct element {
	void *data;
	struct element *next;
} typedef Element;


/* Métodos auxiliares */

/* Esvazia o conteúdo de uma fila. */
static void _empty_queue(Queue *queue)
{
	Element *aux;

	while (queue->start != NULL) {
		aux = queue->start;
		queue->start = queue->start->next;
		free(aux);
	}

	queue->end = NULL;
	queue->size = 0;
}

/* Métodos do TAD. */

Queue *new_queue()
{
	Queue *queue;
	queue = NULL;
	queue = (Queue *)malloc(sizeof(Queue));

	if (queue != NULL) {
		queue->size = 0;
		queue->start = NULL;
		queue->end = NULL;
	}

	return queue;
}


int add_to_queue(Queue *queue, void *data)
{
	if (queue == NULL)
		return NULL_ERROR;

	Element *new = (Element *)malloc(sizeof(Element));

	if (new == NULL)
		return NOT_OK;

	new->data = data;
	new->next = NULL;

	if ((queue->start) == NULL)
		// Não tem ninguém
		queue->start = new;
	else
		// Tem alguém na fila
		queue->end->next = new;

	queue->end = new;
	queue->size++;

	return OK;
}


int remove_from_queue(Queue *queue)
{
	CHECK_QUEUE(queue)
	Element *aux = queue->start;
	queue->start = queue->start->next;

	// if (queue->size == 1) // O mesmo que a verificação abaixo:
	if (queue->start == NULL)
		// Só tinha um.
		queue->end = NULL;

	free(aux);
	queue->size--;

	return OK;
}


int queue_get(Queue *queue, void **data)
{
	CHECK_QUEUE(queue)
	*data = queue->start->data;

	return OK;
}


int queue_size(Queue *queue)
{
	if (queue == NULL)
		return NULL_ERROR;

	return queue->size;
}


void empty_queue(Queue *queue)
{
	if (queue == NULL)
		return;

	_empty_queue(queue);
}


int free_queue(Queue **queue)
{
	if (queue == NULL)
		return NULL_ERROR;

	_empty_queue(*queue);
	free(*queue); // Limpa o nó descritor da memória por completo.
	*queue = NULL;
}


int invert_queue(Queue *queue)
{
	if (queue == NULL)
		return NULL_ERROR;

	if (queue->start == NULL)
		return OK;

	Element *previous = NULL;
	Element *current = queue->start;
	Element *next = current->next;

	// Primeira inversão
	queue->end = current;
	current->next = previous;
	previous = current;
	current = next;

	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	queue->start = previous;

	return OK;
}


int migrate_queue(Queue *to, Queue *from)
{
	if (to == NULL || from == NULL)
		return NULL_ERROR;

	if (to->start == NULL) {
		// Copia
		to->start = from->start;
		to->end = from->end;
		to->size = from->size;
	}
	else if (from->start != NULL) {
		// Transfere/ Anexa (append)
		to->end->next = from->start;
		to->end = from->end;
		to->size += from->size;
	}

	from->start = NULL;
	from->end = NULL;
	from->size = 0;

	return OK;
}
