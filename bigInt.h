#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"

typedef struct bigInt
{
	char val;
	struct bigInt *next;
	struct bigInt *prev;
} bigInt;


void read(stack **head, char c, char sign);
void print(stack *head);
void clear(stack **head);
void push_front(stack *head, char dig);
void push_back(stack *head, char dig);
void pop_front(stack *head);
void pop_back(stack *head);
stack* create();
stack* copy(stack *head);
