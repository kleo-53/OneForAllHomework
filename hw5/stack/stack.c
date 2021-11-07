#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

#define ERROR_VALUE -10000007

bool push(StackElement** head, int number)
{
    StackElement* newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL)
    {
        return false;
    }
    newStackElement->value = number;
    newStackElement->next = *head;
    *head = newStackElement;
    return true;
}

int pop(StackElement** head)
{
    if (*head == NULL)
    {
        return ERROR_VALUE;
    }
    StackElement* temp = *head;
    int value = temp->value;
    *head = (*head)->next;
    free(temp);
    return value;
}

bool isEmpty(StackElement* head)
{
    return head == NULL;
}

void deleteStack(StackElement** head)
{
    while (!isEmpty(*head))
    {
        pop(head);
    }
}