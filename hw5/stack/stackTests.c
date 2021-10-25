#include "stack.h"
#include "stackTests.h"
#include <stdio.h>

bool testStackWorks()
{
    StackElement* stack = NULL;
    push(&stack, 10);
    if (stack->value != 10)
    {
        return false;
    }
    push(&stack, 11);
    if (stack->value != 11)
    {
        return false;
    }
    int popValue = pop(&stack);
    if (popValue != 11 || stack->value != 10)
    {
        return false;
    }
    popValue = pop(&stack);
    if (popValue != 10 || stack != NULL)
    {
        return false;
    }
    return true;
}

bool testPopEmptyStack()
{
    StackElement* stack = NULL;
    const int popValue = pop(&stack);
    return popValue == NULL;
}

bool testIsEmpty()
{
    StackElement* stack = NULL;
    if (!isEmpty(stack))
    {
        return false;
    }
    push(&stack, 10);
     return !isEmpty(stack);
}