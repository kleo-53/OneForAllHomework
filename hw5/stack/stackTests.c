#include "stack.h"
#include "stackTests.h"
#include <stdio.h>

bool testStackWorks()
{
    StackElement* stack = NULL;
    bool isAdded = push(&stack, 10);
    bool isDeleted = true;
    if (!isAdded || stack->value != 10)
    {
        deleteStack(&stack, &isDeleted);
        return false;
    }
    isAdded = push(&stack, 11);
    if (!isAdded || stack->value != 11)
    {
        deleteStack(&stack, &isDeleted);
        return false;
    }
    bool isWorks = true;
    int popValue = pop(&stack, &isWorks);
    if (!isWorks || popValue != 11 || stack->value != 10)
    {
        deleteStack(&stack, &isDeleted);
        return false;
    }
    popValue = pop(&stack, &isWorks);
    if (!isWorks || popValue != 10 || stack != NULL)
    {
        deleteStack(&stack, &isDeleted);
        return false;
    }
    deleteStack(&stack, &isDeleted);
    return true;
}

bool testPopEmptyStack()
{
    StackElement* stack = NULL;
    bool isWorks = true;
    bool isDeleted = true;
    const int popValue = pop(&stack, &isWorks);
    deleteStack(&stack, &isDeleted);
    return !isWorks && isDeleted ? true : false;
}

bool testIsEmpty()
{
    StackElement* stack = NULL;
    bool isDeleted = true;
    if (!isEmpty(stack))
    {
        deleteStack(&stack, &isDeleted);
        return false;
    }
    bool isAdded = push(&stack, 10);
    if (isEmpty(stack) || !isAdded)
    {
        return false;
    }
    deleteStack(&stack, &isDeleted);
    return true;
}