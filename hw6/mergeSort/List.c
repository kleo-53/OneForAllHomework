#include "List.h"
#include <stdlib.h>

typedef struct ListElement
{
    char* name;
    char* phone;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
    ListElement* tail;
    int size;
} List;

List* createList()
{
    List* newList = (List*)calloc(1, sizeof(List));
    newList->size = 0;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

int sizeOfList(List* list)
{
    return list->size;
}

void addElement(List* list, char* name, char* phone)
{
    list->size++;
    char* newName = malloc(strlen(name) + 1);
    char* newPhone = malloc(strlen(phone) + 1);
    strcpy(newName, name);
    strcpy(newPhone, phone);
    ListElement* newElement = malloc(sizeof(ListElement));
    newElement->name = newName;
    newElement->phone = newPhone;
    newElement->next = NULL;

    if (isEmpty(list))
    {
        list->head = newElement;
        list->tail = list->head;
        return;
    }
    list->tail->next = newElement;
    list->tail = list->tail->next;
}

void printList(List* list)
{
    if (isEmpty(list))
    {
        return;
    }
    ListElement* current = list->head;
    while (current != NULL)
    {
        printf("%s: %s\n", current->name, current->phone);
        current = current->next;
    }
}

void deleteList(List* list)
{
    ListElement* temporary = malloc(sizeof(ListElement*));
    while (!isEmpty(list))
    {
        temporary = list->head->next;
        free(list->head->name);
        free(list->head->phone);
        free(list->head);
        list->head = temporary;
    }
    free(list);
}

char* getHeadName(List* list)
{
    return list->head->name;
}

char* getHeadPhone(List* list)
{
    return list->head->phone;
}

void deleteHeadElement(List* list)
{
    if (isEmpty(list))
    {
        return;
    }
    list->size--;
    ListElement* temporary = list->head->next;
    free(list->head->name);
    free(list->head->phone);
    free(list->head);
    list->head = temporary;
}