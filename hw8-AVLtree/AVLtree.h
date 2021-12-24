#pragma once

#include <stdbool.h>

// Struct of AVL-tree
typedef struct Tree Tree;

// This function creates AVL-tree
Tree* createTree();

// This function checks if tree is empty
bool isEmpty(Tree* tree);

// This function adds the key and its value to the tree
void addValue(Tree* tree, char* key, char* value, bool* isWorking);

// This function checks if given key is in tree
bool inTree(Tree* tree, char* key, bool* isWorking);

// This function gets the value in tree by key
char* getValue(Tree* tree, char* key, bool* isWorking);

// This function deletes key and its value from tree
void deleteValue(Tree* tree, char* key, bool* isWorking, bool* result);

// This function deletes the tree
void deleteTree(Tree* tree);

// This function checks if height difference of the childs is <= 1
bool isBalanced(Tree* tree);