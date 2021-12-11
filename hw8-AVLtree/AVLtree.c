#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* leftSon;
    struct Node* rightSon;
    struct Node* parent;
    char* key;
    char* value;
    int balance;
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

Node* leftRotation(Node* root)
{
    Node* base = root->rightSon;
    root->rightSon = base->leftSon;
    if (base->leftSon != NULL)
    {
        base->leftSon->parent = root;
    }
    base->parent = root->parent;
    if (root->parent != NULL)
    {
        if (root->parent->rightSon == root)
        {
            root->parent->rightSon = base;
        }
        else
        {
            root->parent->leftSon = base;
        }
    }
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
    if (root->parent != NULL)
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

Node* balance(Node* node) 
{
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
        node = leftRotation(node);
        return node;
    }
    if (node->balance == -2)
    {
        if (getBalance(node->leftSon) == 1)
        {
            node->leftSon = leftRotation(node->leftSon);
        }
        node = rightRotation(node);
        return node;
    }
    return node;
}

Node* createNode(char* key, Node* node, char* value, bool* isWorking)
{
    Node* newNode = calloc(sizeof(Node), 1);
    if (newNode == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    newNode->key = key;
    newNode->parent = node;
    newNode->value = value;
    newNode->balance = 0;
    return newNode;
}

bool addValueRecursive(Node** node, char* key, char* value, bool* isWorking)
{
    if (strcmp(key, (*node)->key) == 0)
    {
        free((*node)->value);
        (*node)->value = value;
        return false;
    }
    if (strcmp(key, (*node)->key) < 0)
    {
        if ((*node)->leftSon == NULL)
        {
            Node* newNode = createNode(key, *node, value, isWorking);
            (*node)->leftSon = newNode;
            (*node)->balance -= 1;
            *node = balance(*node);
            return (*node)->balance != 0;
        }
        if (addValueRecursive(&((*node)->leftSon), key, value, isWorking))
        {
            (*node)->balance -= 1;
            *node = balance(*node);
            return ((*node)->balance != 0);
        }
        return false;
    }
    if (strcmp(key, (*node)->key) > 0)
    {
        if ((*node)->rightSon == NULL)
        {
            Node* newNode = createNode(key, *node, value, isWorking);
            (*node)->rightSon = newNode;
            (*node)->balance += 1;
            *node = balance(*node);
            return ((*node)->balance != 0);
        }
        if (addValueRecursive(&((*node)->rightSon), key, value, isWorking))
        {
            (*node)->balance += 1;
            *node = balance(*node);
            return ((*node)->balance != 0);
        }
        return false;
    }
    return true;
}

void addValue(Tree* tree, char* key, char* value, bool* isWorking)
{
    char* addedValue = malloc(strlen(value) + 1);
    if (addedValue == NULL)
    {
        isWorking = false;
        return;
    }
    char* addedKey = malloc(strlen(key) + 1);
    if (addedKey == NULL)
    {
        isWorking = false;
        return;
    }
    strcpy(addedValue, value);
    strcpy(addedKey, key);
    if (isEmpty(tree))
    {

        Node* newNode = createNode(addedKey, NULL, addedValue, isWorking);
        tree->root = newNode;
        return;
    }
    addValueRecursive(&(tree->root), addedKey, addedValue, isWorking);
}

char* getValueRecursive(Node* node, char* key, bool* isWorking)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (strcmp(key, node->key) == 0)
    {
        char* value = malloc(sizeof(char*));
        if (value == NULL)
        {
            *isWorking = false;
            return NULL;
        }
        return node->value;
    }
    return (strcmp(key, node->key) < 0) ? getValueRecursive(node->leftSon, key, isWorking) : getValueRecursive(node->rightSon, key, isWorking);
}

char* getValue(Tree* tree, char* key, bool* isWorking)
{
    return getValueRecursive(tree->root, key, isWorking);
}

bool inTree(Tree* tree, char* key, bool* isWorking)
{
    return getValueRecursive(tree->root, key, isWorking) != NULL;
}

Node* subsequentNode(Node* node)
{
    Node* rightInLefts = node->leftSon;
    while (rightInLefts->rightSon != NULL)
    {
        rightInLefts = rightInLefts->rightSon;
    }
    return rightInLefts;
}

Node* deleteNodeRecursive(Node* node, char* key, bool* isWorking, bool* result)
{
    if (node == NULL)
    {
        *result = true;
        return NULL;
    }
    if (strcmp(key, node->key) == 0)
    {
        if (node->leftSon != NULL && node->rightSon != NULL)
        {
            Node* subNode = subsequentNode(node);
            char* value = calloc(sizeof(subNode->value) + 1, sizeof(char*));
            if (value == NULL)
            {
                *isWorking = false;
                *result = true;
                return NULL;
            }
            char* nodeKey = calloc(sizeof(subNode->key) + 1, sizeof(char*));
            if (nodeKey == NULL)
            {
                *isWorking = false;
                *result = true;
                return NULL;
            }
            strcpy(value, subNode->value);
            node->value = value;
            strcpy(nodeKey, subNode->key);
            node->key = nodeKey;
            node->balance = subNode->balance - 1;
            subNode = deleteNodeRecursive(subNode, subNode->key, isWorking, result);
            node = balance(node);
            *result = (node->balance != -1 && node->balance != 1);
            return node;
        }
        if (node->rightSon == NULL)
        {
            if (node->leftSon != NULL)
            {
                node->leftSon->parent = node->parent;
            }

            if (strcmp(key, node->parent->key) <= 0)
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
            if (strcmp(key, node->parent->key) <= 0)
            {
                node->parent->leftSon = node->rightSon;
            }
            else
            {
                node->parent->rightSon = node->rightSon;
            }
        }
        free(node->value);
        free(node->key);
        free(node);
        *result = true;
        return NULL;
    }
    if (strcmp(key, node->key) < 0)
    {
        node->leftSon = deleteNodeRecursive(node->leftSon, key, isWorking, result);
        if (*result)
        {
            node->balance += 1;
            node = balance(node);
            *result = node->balance != -1 && node->balance != 1;
            return node;
        }
        *result = false;
        return node;
    }
    node->rightSon = deleteNodeRecursive(node->rightSon, key, isWorking, result);
    if (*result)
    {
        node->balance -= 1;
        node = balance(node);
        *result = node->balance != -1 && node->balance != 1;
        return node;
    }
    *result = false;
    return node;
}

Node* deleteRoot(Tree* tree, bool* isWork, bool* result)
{
    if (tree->root->leftSon != NULL && tree->root->rightSon != NULL)
    {
        Node* subNode = subsequentNode(tree->root);
        char* value = calloc(sizeof(subNode->value) + 1, sizeof(char));
        if (value == NULL)
        {
            *isWork = false;
            return NULL;
        }
        char* nodeKey = calloc(sizeof(subNode->value) + 1, sizeof(char));
        if (nodeKey == NULL)
        {
            *isWork = false;
            return NULL;
        }
        strcpy(value, subNode->value);
        tree->root->value = value;
        strcpy(nodeKey, subNode->key);
        tree->root->key = nodeKey;
        subNode = deleteNodeRecursive(subNode, subNode->key, isWork, result);
        tree->root->balance -= 1;
        tree->root = balance(tree->root);
        return tree->root;
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
    free(tree->root->key);
    free(tree->root->value);
    free(tree->root);
    tree->root = balance(newRoot);
    return newRoot;
}

void deleteValue(Tree* tree, char* key, bool* isWork, bool* result)
{
    if (isEmpty(tree))
    {
        return;
    }
    if (strcmp(key, tree->root->key) == 0)
    {
        tree->root = deleteRoot(tree, isWork, result);
        return;
    }
    tree->root = deleteNodeRecursive(tree->root, key, isWork, result);
}

void deleteTreeRecursive(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    deleteTreeRecursive(node->leftSon);
    deleteTreeRecursive(node->rightSon);
    free(node);
}

void deleteTree(Tree* tree)
{
    deleteTreeRecursive(tree->root);
    free(tree);
}

int getHeightAndIsBalanced(Node* node, bool* balanceTree)
{
    if (node->leftSon == NULL && node->rightSon == NULL)
    {
        return 0;
    }
    if (node->leftSon == NULL || node->rightSon == NULL)
    {
        return 1;
    }
    int heightLeft = getHeightAndIsBalanced(node->leftSon, balanceTree);
    int heightRight = getHeightAndIsBalanced(node->rightSon, balanceTree);
    if (heightLeft > heightRight)
    {
        *balanceTree = (heightLeft - heightRight) < 2;
    }
    else
    {
        *balanceTree = (heightRight - heightLeft) < 2;
    }
    return (heightLeft > heightRight) ? heightLeft : heightRight + 1;
}

bool isBalanced(Tree* tree)
{
    bool balanceTree = true;
    int height = getHeightAndIsBalanced(tree->root, &balanceTree);
    return balanceTree;
}