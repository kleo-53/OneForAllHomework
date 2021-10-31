#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void push(StackElement** head, int number)
{
    StackElement* newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL)
    {
        return;
    }
    newStackElement->value = number;
    newStackElement->next = *head;
    *head = newStackElement;
}

int pop(StackElement** head)
{
    if (*head == NULL)
    {
        return NULL;
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