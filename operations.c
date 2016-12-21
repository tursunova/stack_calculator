#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"

int cmp(stack *head)
{
	if (head->size > head->next->size)
	{
		return 0; 
	}
	if (head->size < head->next->size)
	{
		return 1; 
	}
	bigInt *a = head->back;
	bigInt *b = head->next->back;
	while ((a->val == b->val) && a->prev)
	{
		a = a->prev;
		b = b->prev;
	}
	if (a->val > b->val)
	{
		return 0;
	}
	if (a->val < b->val)
	{
		return 1;
	}
	return 2;
}



void sum(stack **head)
{
	stack *res = create();
	res->sign = (*head)->next->sign;
	stack *l = (*head);
	stack *r = (*head)->next;
	char d = 0;
	while (l->front && r->front)
	{
		push_back(res, ((r->front->val + l->front->val + d) % 10));
		d = (r->front->val + l->front->val + d) / 10;
		pop_front(l);
		pop_front(r);
	}
	while (l->front)
	{
		push_back(res, ((l->front->val + d) % 10));
		d = (l->front->val + d) / 10;
		pop_front(l);
	}
	while (r->front)
	{
		push_back(res, ((r->front->val + d) % 10));
		d = (r->front->val + d) / 10;
		pop_front(r);
	}
	if (d)
	{
		push_back(res, d);
	}
	clear(head);
	clear(head);
	res->next = *head;
	*head = res;
}

void difference(stack **head)
{
	if (cmp(*head) == 2) 
	{
		clear(head);
		clear(head);
		stack *tmp = create();
		push_front(tmp, 0);
		tmp->next = *head;
		*head = tmp;
		return;
	}
	bigInt *min = NULL;
	bigInt *max = NULL;
	stack *res = create();
	if (cmp(*head))
	{
		min = (*head)->front;
		max = (*head)->next->front;
		res->sign = (*head)->next->sign;
	}
	else
	{
		min = (*head)->next->front;
		max = (*head)->front;
		if ((*head)->sign != (*head)->next->sign)
		{
			res->sign = (*head)->sign;
		}
		else
		{
			res->sign = ((*head)->sign + 1) % 2;
		}
	}
	char d = 0;
	while (max && min)
	{
		d = max->val - min->val;
		if (d < 0)
		{
			d += 10;
			max->next->val--;
		}
		push_back(res, d);
		max = max->next;
		min = min->next;
	}
	while (max)
	{
		while (max->val < 0)
		{
			max->val += 10;
			max->next->val--;
		}
		push_back(res, max->val);
		max = max->next;
	}
	while (!res->back->val && res->back->prev)
	{
		pop_back(res);
	}
	clear(head);
	clear(head); 
	res->next = *head;
	*head = res;
}

void product(stack **head)
{
	if (!(*head) || !(*head)->next)
	{
		printf("empty stack.\n");
		return;
	}
	stack *res = create();
	res->sign = ((*head)->sign == (*head)->next->sign) ? 0 : 1;
	if (!(*head)->back->val || !(*head)->next->back->val) 
	{
		push_front(res, 0);
		res->sign = 0;
		clear(head);
		clear(head);
		res->next = *head;
		*head = res;
		return;
	}
	if (((*head)->back->val == 1) && ((*head)->size == 1))
	{
		(*head)->next->sign = ((*head)->sign == (*head)->next->sign) ? 0 : 1;
		clear(head);
		return;
	}
	if (((*head)->next->back->val == 1) && ((*head)->next->size == 1))
	{
		(*head)->sign = ((*head)->sign == (*head)->next->sign) ? 0 : 1;
		clear(&(*head)->next);
		return;
	}
	bigInt *l = (*head)->front;
	bigInt *r = (*head)->next->front;
	long i = (*head)->size + (*head)->next->size;
	while (i--)
	{
		push_front(res, 0); // res = 0
	}
	char mod = 0;
	char d = 0;
	bigInt *tmp_start = res->front;
	bigInt *tmp = res->front;
	while (l)
	{
		while (r)
		{
			mod = tmp->val;
			tmp->val = ((l->val * r->val) + d + mod) % 10;
			d = ((l->val * r->val) + d + mod) / 10;
			r = r->next;
			tmp = tmp->next;
		}
		while(d)
		{
			mod = tmp->val;
			tmp->val = (d + mod) % 10;
			d = (d + mod) / 10;
			tmp = tmp->next;
		}
		r = (*head)->next->front;
		tmp_start = tmp_start->next;
		tmp = tmp_start;
		l = l->next;
		pop_front(*head);
	}
	while (!res->back->val && res->back->prev)
	{
		pop_back(res);
	}
	clear(head);
	clear(head);
	res->next = *head;
	*head = res;
	return;
}

void quotient(stack **head)
{
	if (!(*head) || !(*head)->next)
	{
		printf("empty stack.\n");
		return;
	}
	if (((*head)->back->val == 1) && ((*head)->size == 1))
	{
		(*head)->next->sign = ((*head)->sign == (*head)->next->sign) ? 0 : 1;
		clear(head);
		return;
	}
	stack *res = create();
	res->sign = ((*head)->sign == (*head)->next->sign) ? 0 : 1;
	// if (a=b) then a/b = +-1
	if (cmp(*head) == 2)
	{
		clear(head);
		clear(head);
		push_front(res, 1);
		res->next = (*head);
		(*head) = res;
		return;
	}
	// if (a<b) then a/b = 0 in Z
	if (!cmp(*head))
	{
		clear(head);
		clear(head);
		push_front(res, 0);
		res->next = *head;
		*head = res;
		return;
	}
	//if a>b then a/b=res
	int quot = 0;
	(*head)->sign = 0;
	(*head)->next->sign = 0;
	stack *t = copy(*head);
	stack *d = create();
	t->next = d;
	while ((*head)->next->back)
	{
		do
		{
			if (d->back && !d->back->val)
			{
				pop_back(d);
			}
			push_front(d, (*head)->next->back->val);
			pop_back((*head)->next);
			if (!cmp(t) && (*head)->next->back)
			{
				push_front(res, 0);
			}
		} while (!cmp(t) && (*head)->next->back);
		while (cmp(t))
		{
			difference(&t);
			quot++;
			d = t;
			t = copy(*head);
			t->next = d;
		}
		push_front(res, quot);
		quot = 0;
	}
	while (!res->back->val && res->back->prev)
	{
		pop_back(res);
	}
	clear(&t);
	clear(&d);
	clear(head);
	clear(head);
	res->next = (*head);
	*head = res;
}
