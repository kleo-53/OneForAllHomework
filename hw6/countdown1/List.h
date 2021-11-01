#pragma once

// Struct of cyclic list
typedef struct List List;

// This function creates new list
List* createList();

// This function adds element to the head of list
void addElement(int value, List* list);

// This function moves the head link to the previous element of list
void passElement(List* list);

// This function deletes head element from list
void deleteElement(List* list);

// This function prints the head element of the list
int printRemaining(List* list);