#include "stack.h"
#include <stdlib.h>

#define CHECK_STACK(STACK)                                                                         \
	if (STACK == NULL)                                                                             \
		return NULL_ERROR;                                                                         \
	if (STACK->current == NULL)                                                                    \
		return EMPTY_ERROR;

struct element {
	void *data;
	struct element *next;
} typedef Element;

// Nó descritor que armazena também o primeiro elemento da pilha.
struct stack {
	Element *first;   // Primeiro elemento que foi inserido na pilha.
	Element *current; // Elemento atual da pilha.
};

Stack *new_stack()
{
	Stack *stack = (Stack *)malloc(sizeof(Stack));

	if (stack != NULL) {
		stack->first = NULL;
		stack->current = NULL;
	}

	return stack;
}


int stack_push(Stack *stack, void *new_data)
{
	if (stack == NULL)
		return NULL_ERROR;

	Element *new = (Element *)malloc(sizeof(Element));

	if (new == NULL)
		return NOT_OK;

	new->data = new_data;
	new->next = stack->current;
	stack->current = new;

	if (stack->first == NULL)
		stack->first = new;

	return OK;
}


int stack_pop(Stack *stack)
{
	CHECK_STACK(stack)
	Element *aux = stack->current;
	stack->current = aux->next;

	if (stack->current == NULL)
		stack->first = NULL;

	free(aux);

	return OK;
}


int stack_get(Stack *stack, void **output)
{
	CHECK_STACK(stack)
	*output = stack->current->data;

	return OK;
}


void empty_stack(Stack *stack)
{
	if (stack == NULL)
		return;

	Element *aux;

	while (stack->current != NULL) {
		aux = stack->current;
		stack->current = aux->next;
		free(aux);
	}

	stack->first = NULL;
	// free(stack);
}


int stack_size(Stack *stack)
{
	if (stack == NULL)
		return NULL_ERROR;

	int value = 0;
	Element *aux = stack->current;

	while (aux != NULL) {
		aux = aux->next;
		++value;
	}

	return value;
}


// Por meio da função `stack_size` já podemos identificar se a stack está vazia.
// int is_stack_empty(Stack *stack)
// {
// 	if (stack == NULL)
// 		return NULL_ERROR;

// 	return *stack == NULL;
// }


int stack_append(Stack *a, Stack **b)
{
	if (a == NULL || b == NULL || *b == NULL)
		return NULL_ERROR;

	// if (*a == NULL && **b == NULL)
	// 	return EMPTY_ERROR; //  EMPTY_ERROR (se ambas forem vazias)

	if (a->current == NULL)
		a->current = (*b)->current;
	else
		a->first->next = (*b)->current; // Insere a segunda pilha abaixo da primeira.

	free(*b); // Não mais precisamos do ponteiro da pilha.
	*b = NULL;

	return OK;
}
