#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"


int main(){
    char c;
    stack *head_stack = NULL;
    while(1){
	c = getchar();
	if (c=='='){
   	    print(head_stack);
	} else if (c == EOF) {
	    while(head_stack){
	        clear(&head_stack);
	    }
	    break;
	} else if (c=='+')
	{
	    if (head_stack && head_stack->next)
	    {
		if (head_stack->sign == head_stack->next->sign)
		{
		    sum(&head_stack);  
		} else {
		    difference(&head_stack);
		}
	    } else {
		printf("empty stack.\n");
	    } 
	} else if (c=='-'){
	    if ((c = getchar()) != '\n')
	    {
		number_read(&head_stack, c, '1');
		continue;
	    }
	    if (head_stack && head_stack->next)
            {
		if (head_stack->sign != head_stack->next->sign)
		{
		    sum(&head_stack); 
		} else {
		    difference(&head_stack);
		}
	    } else {
		printf("empty stack.\n");
	    }
	} else if (c=='*'){
	    product(&head_stack);
	} else if (c=='/'){
	    quotient(&head_stack);
    	} else if (c != '\n'){
	    number_read(&head_stack, c, '0');
        }
    }
}
