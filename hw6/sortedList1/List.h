#pragma once
#include <stdbool.h>

// This is strust of list, it consists of list elements
typedef struct List List;

// This strust consists of elements position
typedef struct Position Position;

// This function creates new list
List* createList();

// This function deletes list
void deleteList(List* list);

// This function checks if list is empty
bool isEmpty(List* list);

// This function give the value by position of value
int get(List * list, Position * position);

// This function finds suitable position to value and add them to list
void addData(List* list, int value);

// This function finds the position by value and deletes them from list
bool deleteData(List* list, int value);

// This function prints the list
void printList(List* list);
