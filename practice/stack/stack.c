#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

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
        return;
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

int main()
{
    StackElement* head = NULL;
    push(&head, 10);
    push(&head, 15);
    isEmpty(&head);
    printf("%d", pop(&head));
    printf("%d", pop(&head));
    return 0;
}