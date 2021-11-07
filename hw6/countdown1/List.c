#include "List.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct ListElement
{
    int value;
    struct ListElement* previous;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    struct ListElement* head;
    int length;
} List;

List* createList()
{
    return calloc(1, sizeof(List));
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

bool addElement(int value, List* list)
{
    ListElement* newElement = calloc(sizeof(ListElement), 1);
    if (newElement == NULL)
    {
        return false;
    }
    newElement->value = value;
    if (isEmpty(list))
    {
        newElement->previous = newElement;
        newElement->next = newElement;
        list->head = newElement;
        ++list->length;
        return true;
    }
    ListElement* previousElement = list->head;
    ListElement* nextElement = previousElement->next;
    nextElement->previous = newElement;
    previousElement->next = newElement;
    newElement->next = nextElement;
    newElement->previous = previousElement;
    ++list->length;
    return true;
}

void passElement(List* list)
{
    list->head = list->head->previous;
}

void deleteElement(List* list)
{
    ListElement* firstElement = list->head;
    ListElement* nextElement = firstElement->next;
    ListElement* previousElement = firstElement->previous;
    if (firstElement == previousElement)
    {
        free(firstElement);
        list->head = NULL;
        list->length = 0;
        return;
    }
    nextElement->previous = previousElement;
    previousElement->next = nextElement;
    list->head = previousElement;
    --list->length;
    free(firstElement);
}

int getRemaining(List* list)
{
    if (isEmpty(list))
    {
        return -1;
    }
    return list->head->value;
}

int getLength(List* list)
{
    return list->length;
}