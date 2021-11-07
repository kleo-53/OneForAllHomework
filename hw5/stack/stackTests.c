#include "stack.h"
#include "stackTests.h"
#include <stdio.h>

#define ERROR_VALUE -10000007

bool testStackWorks()
{
    StackElement* stack = NULL;
    bool isAdded = push(&stack, 10);
    if (!isAdded || stack->value != 10)
    {
        deleteStack(&stack);
        return false;
    }
    isAdded = push(&stack, 11);
    if (!isAdded || stack->value != 11)
    {
        deleteStack(&stack);
        return false;
    }
    int popValue = pop(&stack);
    if (popValue != 11 || stack->value != 10)
    {
        deleteStack(&stack);
        return false;
    }
    popValue = pop(&stack);
    if (popValue == 10 && stack == NULL) 
    {
        return true;
    }
    deleteStack(&stack);
    return false;
}

bool testPopEmptyStack()
{
    StackElement* stack = NULL;
    const int popValue = pop(&stack);
    deleteStack(&stack);
    return popValue == ERROR_VALUE;
}

bool testIsEmpty()
{
    StackElement* stack = NULL;
    if (!isEmpty(stack))
    {
        deleteStack(&stack);
        return false;
    }
    bool isAdded = push(&stack, 10);
    if (isEmpty(stack) || !isAdded)
    {
        return false;
    }
    deleteStack(&stack);
    return true;
}