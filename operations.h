#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "bigInt.h"
#include "operations.h"
#include "stackStruct.h"

int cmp(stack *head);
void sum(stack **head);
void difference(stack **head);
void product(stack **head);
void quotient(stack **head);
