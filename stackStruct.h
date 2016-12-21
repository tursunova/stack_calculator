#pragma once


typedef struct stack
{
	char sign;
	int size;
	struct bigInt *front;
	struct bigInt *back;
	struct stack *next;
} stack;
