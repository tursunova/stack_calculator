#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"

stack* create()
{
	stack *a = (stack*)malloc(sizeof(stack));
	a->front = NULL;
	a->back = NULL;
	a->next = NULL;
	a->sign = 0;
	a->size = 0;
	return a;
}

void read(stack **head, char c, char sign)
{
	stack *a = create();
	push_front(a, c - '0');
	while ((c = getchar()) != '\n')
	{
		push_front(a, c - '0');
	}
	a->sign = sign - '0';
	a->next = *head;
	*head = a;
}

void print(stack *head)
{
	if (head && head->back)
	{
		bigInt *a = head->back;
		if (head->sign)           
		{
			printf("%c", '-');
		}
		while (a>0)
		{
			printf("%d", a->val);
			a = a->prev;
		}
	}
	else
	{
		printf("empty stack\n");
	}
}

stack* copy(stack *head)
{
	stack *a = create();
	a->sign = head->sign;
	bigInt *num = head->front;
	while (num)
	{
		push_back(a, num->val);
		num = num->next;
	}
	return a;
}

void clear(stack **head)
{
	if (*head)
	{
		while ((*head)->front)
		{
			pop_front(*head);
		}
		stack *op = (*head);
		*head = (*head)->next;
		free(op);
		op = NULL;
        }
}

void push_front(stack *head, char val)
{
	bigInt *a = (bigInt*)malloc(sizeof(bigInt));
	a->val = val;
	a->prev = NULL;
	a->next = head->front;
	if (head->front)
	{
		head->front->prev = a;
	}
	else
	{
		head->back = a;
	}
	head->front = a;
	head->size++;
}

void push_back(stack *head, char val)
{
	bigInt *a = (bigInt*)malloc(sizeof(bigInt));
	a->val = val;
	a->next = NULL;
	a->prev = head->back;
	if (head->back)
	{
		head->back->next = a;
	}
	else
	{
		head->front = a;
	}
	head->back = a;
	head->size++;
}

void pop_front(stack *head)
{
	bigInt *a = head->front;
	head->front = head->front->next;
	if (head->front)
	{
		head->front->prev = NULL;
	}
	else
	{
		head->back = NULL;
	}
	free(a);
	a = NULL;
	head->size--;
}

void pop_back(stack *head)
{
	bigInt *a = head->back;
	head->back = head->back->prev;
	if (head->back)
	{
		head->back->next = NULL;
	}
	else
	{
		head->front = NULL;
	}
	free(a);
	a = NULL;
	head->size--;
}
