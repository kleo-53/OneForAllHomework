#pragma once
#pragma once
#include <stdio.h>
#include <stdbool.h>

// This is strust of list, it consists of list elements
typedef struct List List;

// This strust consists of elements position
typedef struct Position Position;

// This function creates new list
List* createList();

// This function deletes list
void deleteList(List* list);

// This function finds suitable position to value and add them to list
bool addData(List* list, int value);

// This function reverses the given list
void reverse(List** list);

// This function prints the list
void printList(List* list);

// This function prints the list into test file
void printListInFile(List* list, FILE* file);