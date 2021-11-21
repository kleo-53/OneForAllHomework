#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* leftSon;
    struct Node* rightSon;
    struct Node* parent;
    int key;
    char* value;
    int balance;
} Node;

typedef struct Tree
{
    Node* root;
}
Tree;

Tree* createTree()
{
    return calloc(sizeof(Tree), 1);
}

bool isEmpty(Tree* tree)
{
    return tree->root == NULL;
}

Node* leftRotation(Node* root)
{
    Node* base = root->rightSon;
    root->rightSon = base->leftSon;
    if (base->leftSon)
    {
        base->leftSon->parent = root;
    }
    base->parent = root->parent;
    if (root->parent)
    {
        if (root->parent->leftSon == root)
        {
            root->parent->leftSon = base;
        }
        else
        {
            root->parent->rightSon = base;
        }
    }
    //else 
    //  rootTree = base
    base->leftSon = root;
    root->parent = base;
    if (base->balance == 0)
    {
        root->balance = 1;
        base->balance = -1;
    }
    else
    {
        root->balance = 0;
        base->balance = 0;
    }
    return base;
}

Node* rightRotation(Node* root)
{
    Node* base = root->leftSon;
    root->leftSon = base->rightSon;
    base->parent = root->parent;
    if (base->rightSon != NULL)
    {
        base->rightSon->parent = root;
    }
    base->parent = root->parent;
    if (root->parent)
    {
        if (root->parent->leftSon == root)
        {
            root->parent->leftSon = base;
        }
        else
        {
            root->parent->rightSon = base;
        }
    }
    //else 
    //  rootTree = root
    base->rightSon = root;
    root->parent = base;
    if (base->balance == 0)
    {
        root->balance = -1;
        base->balance = 1;
    }
    else
    {
        root->balance = 0;
        base->balance = 0;
    }
    return base;
}

int getBalance(Node* node)
{
    return node == NULL ? 0 : node->balance;
}

Node* balance(Node* node) {
    if (node == NULL)
    {
        return node;
    }
    if (node->balance == 2)
    {
        if (getBalance(node->rightSon) == -1)
        {
            node->rightSon = rightRotation(node->rightSon);
        }
        return leftRotation(node);
    }
    if (node->balance == -2)
    {
        if (getBalance(node->leftSon) == 1)
        {
            node->leftSon = leftRotation(node->leftSon);
        }
        return rightRotation(node);
    }
    return node;
}

bool addValueRecursive(Node* node, int key, char* value, bool* isWork)
{
    if (key == node->key)
    {
        node->value = value;
        return false;
    }
    if (key < node->key)
    {
        if (node->leftSon == NULL)
        {
            Node* newNode = calloc(sizeof(Node), 1);
            if (newNode == NULL)
            {
                *isWork = false;
                return;
            }
            newNode->key = key;
            newNode->parent = node;
            newNode->value = value;
            newNode->balance = 0;
            node->leftSon = newNode;
            node->balance -= 1;
            node = balance(node);
            return (node->balance != 0);
        }
        if (addValueRecursive(node->leftSon, key, value, isWork) == true)
        {
            node->balance -= 1;
            node = balance(node);
            return (node->balance != 0);
        }
        return false;
    }
    if (key > node->key)
    {
        if (node->rightSon == NULL)
        {
            Node* newNode = calloc(sizeof(Node), 1);
            newNode->key = key;
            newNode->parent = node;
            newNode->value = value;
            newNode->balance = 0;
            node->rightSon = newNode;
            node->balance += 1;
            node = balance(node);
            return (node->balance != 0);
        }
        if (addValueRecursive(node->rightSon, key, value, isWork) == true)
        {
            node->balance += 1;
            node = balance(node);
            return (node->balance != 0);
        }
        return false;
    }
    return true;
}

void addValue(Tree* tree, int key, char* value, bool* isWork)
{
    char* addedValue = malloc(strlen(value) + 1);
    if (addedValue == NULL)
    {
        isWork = false;
        return;
    }
    strcpy(addedValue, value);
    if (isEmpty(tree))
    {
        Node* newNode = calloc(sizeof(Node), 1);
        if (newNode == NULL)
        {
            *isWork = false;
            return;
        }
        newNode->key = key;
        newNode->value = addedValue;
        newNode->balance = 0;
        tree->root = newNode;
        return;
    }
    addValueRecursive(tree->root, key, addedValue, isWork);
    return;
}

bool inTreeRecursive(Node* node, int key)
{
    if (node == NULL)
    {
        return false;
    }
    if (key == node->key)
    {
        return true;
    }
    return (key < node->key) ? inTreeRecursive(node->leftSon, key) : inTreeRecursive(node->rightSon, key);
}

bool inTree(Tree* tree, int key)
{
    return inTreeRecursive(tree->root, key);
}

char* getValueRecursive(Node* node, int key, bool* isWork)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (key == node->key)
    {
        char* value = malloc(sizeof(char*));
        if (value == NULL)
        {
            *isWork = false;
            return NULL;
        }
        strcpy(value, node->value);
        return value;
    }
    return (key < node->key) ? getValueRecursive(node->leftSon, key, isWork) : getValueRecursive(node->rightSon, key, isWork);
}

char* getValue(Tree* tree, int key, bool* isWork)
{
    return getValueRecursive(tree->root, key, isWork);
}

Node* subsequentNode(Node* node)
{
    Node* leftInRights = node->leftSon;
    int lengthRight = 1;
    while (leftInRights->leftSon != NULL)
    {
        leftInRights = leftInRights->leftSon;
        ++lengthRight;
    }
    Node* rightInLefts = node->leftSon;
    int lengthLeft = 1;
    while (rightInLefts->leftSon != NULL)
    {
        rightInLefts = rightInLefts->leftSon;
        ++lengthLeft;
    }
    return (lengthLeft < lengthRight) ? leftInRights : rightInLefts;
}
bool deleteNodeRecursive(Node* node, int key, bool* isWork)
{
    if (node == NULL)
    {
        return;
    }
    if (key == node->key)
    {
        if (node->leftSon != NULL && node->rightSon != NULL)
        {
            Node* subNode = subsequentNode(node);
            char* value = calloc(sizeof(subNode->value) + 1, sizeof(char*));
            if (value == NULL)
            {
                *isWork = false;
                return;
            }
            strcpy(value, subNode->value);
            node->value = value;
            node->key = subNode->key;
            node->balance = subNode->balance;
            free(subNode);
            node = balance(node);
            return (node->balance != -1 && node->balance != 1);
        }
        if (node->rightSon == NULL)
        {
            if (node->leftSon != NULL)
            {
                node->leftSon->parent = node->parent;
            }

            if (key < node->parent->key)
            {
                node->parent->leftSon = node->leftSon;
            }
            else
            {
                node->parent->rightSon = node->leftSon;
            }
        }
        else
        {
            node->rightSon->parent = node->parent;
            if (key < node->parent->key)
            {
                node->parent->leftSon = node->rightSon;
            }
            else
            {
                node->parent->rightSon = node->rightSon;
            }
        }
        //free(node->value);
        free(node);
        return true;
    }
    if (key < node->key)
    {
        if (deleteNodeRecursive(node->leftSon, key, isWork) == true)
        {
            node->balance += 1;
            node = balance(node);
            return (node->balance != -1 && node->balance != 1);
        }
        return false;
    }
    else
    {
        if (deleteNodeRecursive(node->rightSon, key, isWork) == true)
        {
            node->balance -= 1;
            node = balance(node);
            return (node->balance != -1 && node->balance != 1);
        }
        return false;
    }
}

void deleteRoot(Tree* tree, bool* isWork)
{
    if (tree->root->leftSon != NULL && tree->root->rightSon != NULL)
    {
        Node* subNode = subsequentNode(tree->root);
        char* value = calloc(sizeof(subNode->value) + 1, sizeof(char));
        if (value == NULL)
        {
            *isWork = false;
            return;
        }
        strcpy(value, subNode->value);
        free(subNode->value);
        tree->root->value = value;
        tree->root->key = subNode->key;
        deleteNodeRecursive(subNode, subNode->key, isWork);
        tree->root = balance(tree->root);
        return;
    }
    Node* newRoot = NULL;
    if (tree->root->leftSon != NULL)
    {
        newRoot = tree->root->leftSon;
    }
    else
    {
        newRoot = tree->root->rightSon;
    }
    if (newRoot != NULL)
    {
        newRoot->parent = NULL;
    }
    free(tree->root->value);
    free(tree->root);
    tree->root = balance(newRoot);
}


void deleteValue(Tree* tree, int key, bool* isWork)
{
    if (isEmpty(tree))
    {
        return;
    }
    if (key == tree->root->key)
    {
        deleteRoot(tree, isWork);
        return;
    }
    deleteNodeRecursive(tree->root, key, isWork);
}

void deleteTreeRecursive(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    deleteTreeRecursive(node->leftSon);
    deleteTreeRecursive(node->rightSon);
    free(node->value);
    free(node);
    return;
}

void deleteTree(Tree* tree)
{
    deleteTreeRecursive(tree->root);
    free(tree);
}