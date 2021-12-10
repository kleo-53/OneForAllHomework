#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    struct Node* leftSon;
    struct Node* rightSon;
    int key;
    char* value;
} Node;

typedef struct Tree
{
    Node* root;
} Tree;

Tree* createTree()
{
    return calloc(sizeof(Tree), 1);
}

bool isEmpty(Tree* tree)
{
    return tree->root == NULL;
}

void addValueRecursive(Node* node, int key, const char* value, bool* isWorking)
{
    char* strValue = calloc(strlen(value) + 1, sizeof(char));
    if (strValue == NULL)
    {
        *isWorking = false;
        return;
    }
    strcpy(strValue, value);
    if (node->key == key)
    {
        strcpy(node->value, strValue);
        free(strValue);
        return;
    }
    if (node->key > key)
    {
        if (node->leftSon == NULL)
        {
            node->leftSon = calloc(sizeof(Node), 1);
            if (node->leftSon == NULL)
            {
                *isWorking = false;
                free(strValue);
                return;
            }
            node->leftSon->key = key;
            node->leftSon->value = strValue;
            return;
        }
        addValueRecursive(node->leftSon, key, value, isWorking);
    }
    if (node->key < key)
    {
        if (node->rightSon == NULL)
        {
            node->rightSon = calloc(sizeof(Node), 1);
            if (node->rightSon == NULL)
            {
                *isWorking = false;
                free(strValue);
                return;
            }
            node->rightSon->key = key;
            node->rightSon->value = strValue;
            return;
        }
        addValueRecursive(node->rightSon, key, strValue, isWorking);
    }
}

void addValue(Tree* tree, int key, const char* value, bool* isWorking)
{
    if (!isEmpty(tree))
    {
        addValueRecursive(tree->root, key, value, isWorking);
        return;
    }
    char* strValue = calloc(strlen(value) + 1, sizeof(char));
    if (strValue == NULL)
    {
        *isWorking = false;
        return;
    }
    strcpy(strValue, value);
    tree->root = calloc(sizeof(Node), 1);
    if (tree->root == NULL)
    {
        *isWorking = false;
        return;
    }
    tree->root->key = key;
    tree->root->value = strValue;
}

bool inTree(Tree* tree, int key)
{
    Node* i = tree->root;
    while (i != NULL)
    {
        if (key > i->key)
        {
            i = i->rightSon;
        }
        else if (key < i->key)
        {
            i = i->leftSon;
        }
        else
        {
            return true;
        }
    }
    return false;
}

char* getValueRecursive(Node* node, int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->key == key)
    {
        return node->value;
    }
    if (node->key < key)
    {
        return getValueRecursive(node->rightSon, key);
    }
    return getValueRecursive(node->leftSon, key);
}

char* getValue(Tree* tree, int key)
{
    return getValueRecursive(tree->root, key);
}

Node* subsequentNode(Node* node)
{
    Node* right = node->rightSon;
    while (right->leftSon != NULL)
    {
        right = right->leftSon;
    }
    return right;
}

Node* deleteNode(Node* node, int key, bool* isWorking)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->key == key)
    {
        if (node->leftSon == NULL && node->rightSon == NULL)
        {
            free(node->value);
            free(node);
            return NULL;
        }
        else if (node->leftSon == NULL || node->rightSon == NULL)
        {
            Node* child = (node->leftSon != NULL ? node->leftSon : node->rightSon);
            free(node->value);
            free(node);
            return child;
        }
        else
        {
            Node* subsequent = subsequentNode(node);
            node->key = subsequent->key;
            free(node->value);
            node->value = calloc(strlen(subsequent->value) + 1, sizeof(char));
            if (node->value == NULL)
            {
                *isWorking = false;
                return node;
            }
            strcpy(node->value, subsequent->value);
            node->rightSon = deleteNode(node->rightSon, node->rightSon->key, isWorking);
        }
        return node;
    }
    if (node->key > key)
    {
        node->leftSon = deleteNode(node->leftSon, key, isWorking);
        return node;
    }
    else
    {
        node->rightSon = deleteNode(node->rightSon, key, isWorking);
        return node;
    }
}

void deleteValue(Tree* tree, int key, bool* isWorking)
{
    tree->root = deleteNode(tree->root, key, isWorking);
}

void deleteChildren(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    deleteChildren(node->leftSon);
    deleteChildren(node->rightSon);
    free(node);
}

void deleteTree(Tree* tree)
{
    deleteChildren(tree->root);
    free(tree);
}