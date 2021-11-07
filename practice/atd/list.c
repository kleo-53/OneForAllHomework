#include "list.h"
#include <stdlib.h>

typedef struct ListElement 
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct Position
{
    ListElement* position;
} Position;

typedef struct List 
{
    ListElement* head;
} List;

List* createList()
{
    return calloc(1, sizeof(List));
}

void deleteList(List* list)
{
    ListElement* pos = list->head;
    while (pos != NULL)
    {
        list->head = list->head->next;
        free(pos);
        pos = list->head;
    }
    free(list);
}

void deletePosition(Position* position)
{
    free(position);
}


void add(List* list, Position* position, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (position->position == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

Position* first(List* list)
{
    Position* positionFirst = malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* next(Position* position)
{
    Position* positionNext = malloc(1, sizeof(Position));
    positionNext->position = position->position->next;
    return positionNext;
}

bool last(Position* position)
{
    return position->position == NULL;
}

int get(List* list, Position* position)
{
    return position->position->value;
}