#pragma once
#include <stdbool.h>

typedef struct List List;


List* createList();


bool isEmpty(List* list);


void addElement(List* list, char* name, char* phone);


void printList(List* list);


void deleteList(List* list);


int sizeOfList(List* list);


char* getHeadName(List* list);


char* getHeadPhone(List* list);


void deleteHeadElement(List* list);