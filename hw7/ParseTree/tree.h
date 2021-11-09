#pragma once

#include <stdbool.h>

// Struct of dictionary tree, where each node consists of a key, a value, and references to two sons
typedef struct Tree Tree;

// This function creates empty tree
Tree* createAndAdd(char* givenString, bool isWork);

// This function deletes tree
void deleteTree(Tree* tree);

// This function checks if the tree is empty
bool isEmpty(Tree* tree);

// This function adds value by key
int doCalculation(Tree* tree);

// This function checks if this key is in the tree
void printTree(Tree* tree);

// This function gives the value by key
void deleteTree(Tree* tree);
