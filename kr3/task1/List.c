#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
    int a;
    int b;
} List;

typedef struct Position
{
    ListElement* position;
} Position;

List* createList(int a, int b)
{
    List* list = (List*)calloc(1, sizeof(List*));
    if (list == NULL)
    {
        return NULL;
    }
    list->a = a;
    list->b = b;
    return list;
}

void deleteList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
}

bool addData(List* list, int value)
{
    ListElement* current = list->head;
    ListElement* previous = NULL;
    if (value < list->a)
    {
        while (current != NULL && current->value < list->a)
        {
            previous = current;
            current = current->next;
        }
    }
    else if (value >= list->a && value <= list->b)
    {
        while (current != NULL && current->value <= list->b)
        {
            previous = current;
            current = current->next;
        }
    }
    else
    {
        while (current != NULL)
        {
            previous = current;
            current = current->next;
        }
    }
    ListElement * newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return false;
    }
    newElement->next = current;
    newElement->value = value;
    if (previous == NULL)
    {
        list->head = newElement;
    }
    else
    {
        previous->next = newElement;
    }
    return true;
}

void printList(List* list)
{
    ListElement* current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
}

void printListInFile(List* list, FILE* file)
{
    ListElement* current = list->head;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->value);
        current = current->next;
    }
}