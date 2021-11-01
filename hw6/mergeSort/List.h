#pragma once
#include <stdbool.h>

// This is strust of list, it consists of links to previous and next elenents and size of list
typedef struct List List;

// This function creates empty list
List* createList();

// This function checks if list is empty
bool isEmpty(List* list);

// This function adds element to the list
void addElement(List* list, char* name, char* phone);

// This function prints the list
void printList(List* list);

// This function deletes list
void deleteList(List* list);

// This function gives the current size of the list
int sizeOfList(List* list);

// This function gives the name of the first element
char* getHeadName(List* list);

// This function gives the phone of the first element
char* getHeadPhone(List* list);

// This function deletes head element from list
void deleteHeadElement(List* list);