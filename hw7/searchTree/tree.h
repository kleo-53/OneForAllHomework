#pragma once

#include <stdbool.h>

// Struct of dictionary tree, where each node consists of a key, a value, and references to two sons
typedef struct Tree Tree;

// This function creates empty tree
Tree* createTree();

// This function deletes tree
void deleteTree(Tree* tree);

// This function checks if the tree is empty
bool isEmpty(Tree* tree);

// This function adds value by key
void addValue(Tree* tree, int key, char* value, bool isWork);

// This function checks if this key is in the tree
bool inTree(Tree* tree, int key);

// This function gives the value by key
char* getValue(Tree* tree, int key);

// This function deletes the key and the value from the tree
void deleteValue(Tree* tree, int key, bool isWork);

