#define _CRT_SECURE_NO_WARNINGS

#include "List.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

bool addElement(List* list, char* name, char* phone)
{
    char* newName = malloc(strlen(name) + 1);
    if (newName == NULL)
    {
        return false;
    }
    char* newPhone = malloc(strlen(phone) + 1);
    if (newPhone == NULL)
    {
        free(newName);
        return false;
    }
    strcpy(newName, name);
    strcpy(newPhone, phone);
    ListElement* newElement = malloc(sizeof(ListElement));
    if (newElement == NULL)
    {
        free(newName);
        free(newPhone);
        return false;
    }
    newElement->name = newName;
    newElement->phone = newPhone;
    newElement->next = NULL;
    list->size++;
    if (isEmpty(list))
    {
        list->head = newElement;
        list->tail = list->head;
        return true;
    }
    list->tail->next = newElement;
    list->tail = list->tail->next;
    return true;
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
    ListElement* temporary = list->head;
    while (temporary != NULL)
    {
        list->head = list->head->next;
        free(temporary->name);
        free(temporary->phone);
        free(temporary);
        temporary = list->head;
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
