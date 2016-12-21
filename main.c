#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"


int main(){
    char c;
    stack *head = NULL;
    while(1){
	c = getchar();
	if (c=='='){
   	    print(head);
	} else if (c == EOF) {
	    while(head){
	        clear(&head);
	    }
	    break;
	} else if (c=='+')
	{
	    if (head && head->next)
	    {
		if (head->sign == head->next->sign)
		{
		    sum(&head);  
		} else {
		    difference(&head);
		}
	    } else {
		printf("empty stack.\n");
	    } 
	} else if (c=='-'){
	    if ((c = getchar()) != '\n')
	    {
		read(&head, c, '1');
		continue;
	    }
	    if (head && head->next)
            {
		if (head->sign != head->next->sign)
		{
		    sum(&head); 
		} else {
		    difference(&head);
		}
	    } else {
		printf("empty stack.\n");
	    }
	} else if (c=='*'){
	    product(&head);
	} else if (c=='/'){
	    quotient(&head);
    	} else if (c != '\n'){
	    read(&head, c, '0');
        }
    }
}
