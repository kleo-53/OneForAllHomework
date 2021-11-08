#define _CRT_SECURE_NO_WARNINGS

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

void addValueRecursive(Node* node, int key, char* value)
{
    char* strValue = calloc(strlen(value) + 1, sizeof(char));
    strcpy(strValue, value);
    if (node->key == key)
    {
        node->value = strValue;
        return;
    }
    if (node->key > key)
    {
        if (node->leftSon == NULL)
        {
            node->leftSon = calloc(sizeof(Node), 1);
            node->leftSon->key = key;
            node->leftSon->value = strValue;
            return;
        }
        addValueRecursive(node->leftSon, key, value);
    }
    if (node->key < key)
    {
        if (node->rightSon == NULL)
        {
            node->rightSon = calloc(sizeof(Node), 1);
            node->rightSon->key = key;
            node->rightSon->value = strValue;
            return;
        }
        addValueRecursive(node->rightSon, key, strValue);
    }
}

void addValue(Tree* tree, int key, char* value)
{
    if (!isEmpty(tree))
    {
        addValueRecursive(tree->root, key, value);
        return;
    }
    char* strValue = calloc(strlen(value) + 1, sizeof(char));
    strcpy(strValue, value);
    tree->root = calloc(sizeof(Node), 1);
    tree->root->key = key;
    tree->root->value = strValue;
    return;
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
        return "err";
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

Node* deleteNode(Node* node, int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->key == key)
    {
        if (node->leftSon == NULL && node->rightSon == NULL)
        {
            free(node);
            return NULL;
        }
        else if (node->leftSon == NULL || node->rightSon == NULL)
        {
            Node* child = (node->leftSon != NULL ? node->leftSon : node->rightSon);
            free(node);
            node = child;
            return node;
        }
        else
        {
            Node* subsequent = subsequentNode(node);
            node->key = subsequent->key;
            node->value = subsequent->value;
            node->rightSon = deleteNode(node->rightSon, node->rightSon->key);
        }
        return node;
    }
    if (node->key > key)
    {
        node->leftSon = deleteNode(node->leftSon, key);
        return node;
    }
    else
    {
        node->rightSon = deleteNode(node->rightSon, key);
        return node;
    }
}

void deleteValue(Tree* tree, int key)
{
    tree->root = deleteNode(tree->root, key);
    return;
}

void deleteChildren(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    deleteChildren(node->leftSon);
    deleteChildren(node->rightSon);
    free(node->value);
    free(node);
}

void deleteTree(Tree* tree)
{
    deleteChildren(tree->root);
    free(tree);
    return;
}
/*
int main()
{
    Node* ourTree = createTree();
    ourTree = addNode(ourTree, 1);
    ourTree = addNode(ourTree, 2);
    ourTree = addNode(ourTree, 3);
    ourTree = addNode(ourTree, 4);
    bool twoInTree = inTree(&ourTree, 2);
    bool fiveInTree = inTree(&ourTree, 5);
    deleteTree(&ourTree);
}*/