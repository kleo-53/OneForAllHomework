#pragma once

#include <stdbool.h>

// A stack structure that consists of a value and a pointer to the next element
typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

// This function adds an element to the beginning of the stack
bool push(StackElement** head, int number);

// This function deletes an element of the beginning of the stack
int pop(StackElement** head);

// This boolean function checks if stack is empty
bool isEmpty(StackElement* head);

// This function deletes stack and frees the memory
void deleteStack(StackElement** head);