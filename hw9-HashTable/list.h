#pragma once
#include <stdio.h>
#include <stdbool.h>

// This is strust of list, it consists of list elements
typedef struct List List;

// This function creates new list
List* createList();

// This function adds the word and its frequency to list
bool addWord(List* list, char* givenWord, int currentCount, bool* isWorking);

// This function gives the length of the list
int listLength(List* list);

// This function deletes word from head of the list
void deleteFromHead(List* list);

// This function deletes list
void deleteList(List* list);

// This function checks if list is empty
bool isEmpty(List* list);

// This function checks if such word appears in list
bool inList(List* list, char* word);

// This function prints the list
void printList(List* list);

// This function prints the list into test file
void printListInFile(List* list, FILE* file);