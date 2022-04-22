#define _CRT_SECURE_NO_WARNINGS

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement
{
    char* word;
    int counter;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    int length;
    ListElement* head;
} List;

List* createList()
{
    return (List*)calloc(1, sizeof(List));
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

int listLength(List* list)
{
    return list->length;
}

bool addWord(List* list, char* givenWord, int currentCount, bool* isWorking)
{
    ListElement* current = list->head;
    ListElement* previous = NULL;
    while (current != NULL && strcmp(current->word, givenWord) != 0)
    {
        previous = current;
        current = current->next;
    }
    if (current != NULL)
    {
        current->counter += currentCount;
        return false;
    }
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        *isWorking = false;
        return false;
    }
    char* newValue = malloc(strlen(givenWord) + 1);
    if (newValue == NULL)
    {
        *isWorking = false;
        return false;
    }
    newElement->counter = currentCount;
    newElement->next = NULL;
    strcpy(newValue, givenWord);
    newElement->word = newValue;
    if (previous == NULL)
    {
        list->head = newElement;
    }
    else
    {
        previous->next = newElement;
    }
    ++list->length;
    return true;
}

bool inList(List* list, char* word)
{
    ListElement* current = list->head;
    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

int quantityFromHead(List* list)
{
    return list->head->counter;
}

char* returnFromHead(List* list)
{
    if (isEmpty(list))
    {
        return NULL;
    }
    return list->head->word;
}

void deleteFromHead(List* list)
{
    if (isEmpty(list))
    {
        return;
    }
    ListElement* current = list->head;
    list->head = list->head->next;
    free(current);
}

void deleteList(List* list)
{
    while (!isEmpty(list))
    {
        deleteFromHead(list);
    }
    free(list);
}

void printList(List* list)
{
    ListElement* current = list->head;
    while (current != NULL)
    {
        printf("%s - %d times\n", current->word, current->counter);
        current = current->next;
    }
}

void printListInFile(List* list, FILE* file)
{
    ListElement* current = list->head;
    while (current != NULL)
    {
        fprintf(file, "%s - %d times", current->word, current->counter);
        current = current->next;
    }
}