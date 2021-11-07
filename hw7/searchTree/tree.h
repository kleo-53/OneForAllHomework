#pragma once

#include <stdbool.h>

typedef struct Tree Tree;


Tree* createTree();


void deleteTree(Tree* tree);


bool isEmpty(Tree* tree);


void addValue(Tree* tree, int key, char* value);


bool inTree(Tree* tree, int key);


char* getValue(Tree* tree, int key);

void deleteValue(Tree* tree, int key);

