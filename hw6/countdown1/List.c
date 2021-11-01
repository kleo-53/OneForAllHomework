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
} List;

List* createList()
{
    List* newList = malloc(sizeof(List*));
    newList->head = NULL;
    return newList;
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

void addElement(int value, List* list)
{
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->value = value;
    newElement->previous = NULL;
    newElement->next = NULL;
    if (isEmpty(list))
    {
        newElement->previous = newElement;
        newElement->next = newElement;
        list->head = newElement;
        return;
    }
    ListElement* previousElement = list->head;
    ListElement* nextElement = previousElement->next;
    nextElement->previous = newElement;
    previousElement->next = newElement;
    newElement->next = nextElement;
    newElement->previous = previousElement;
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
        free(nextElement);
        free(previousElement);
        list->head = NULL;
        return;
    }
    nextElement->previous = previousElement;
    previousElement->next = nextElement;
    list->head = previousElement;
    free(firstElement);
}

int printRemaining(List* list)
{
    if (isEmpty(list))
    {
        return -1;
    }
    return list->head->value;
}