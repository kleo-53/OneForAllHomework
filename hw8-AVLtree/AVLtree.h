#pragma once

#include <stdbool.h>

// Struct of AVL-tree, consists of nodes, each node consists of key, value and links to the left son, right son and parent 
typedef struct Tree Tree;

// This function creates AVL-tree
Tree* createTree();

// This function checks if tree is empty
bool isEmpty(Tree* tree);

// This function adds the key and its value to the tree
void addValue(Tree* tree, int key, char* value, bool* isWork);

// This function checks if given key is in tree
bool inTree(Tree* tree, int key);

// This function gets the value in tree by key
char* getValue(Tree* tree, int key, bool* isWork);

// This function deletes key and its value from tree
void deleteValue(Tree* tree, int key, bool* isWork, bool* result);

// This function deletes the tree
void deleteTree(Tree* tree);