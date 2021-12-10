#pragma once
#include <stdbool.h>

// Struct of dictionary tree
typedef struct Tree Tree;

// This function creates a tree by given string
Tree* createAndAdd(const char* givenString, bool* isWorking);

// This function deletes tree
void deleteTree(Tree* tree);

// This function checks if the tree is empty
bool isEmpty(Tree* tree);

// This function calculates the result of all operations
int doCalculation(Tree* tree, bool* isWorking);

// This function prints the tree
void printTree(Tree* tree);
