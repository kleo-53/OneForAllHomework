#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char operation;
    int operand;
    struct Node* leftSon;
    struct Node* rightSon;
} Node;

typedef struct Tree
{
    Node* root;
} Tree;

bool isEmpty(Tree* tree)
{
    return tree->root == NULL;
}

int numberConvert(const char* givenString, int* index)
{
    int number = 0;
    while (givenString[*index] >= '0' && givenString[*index] <= '9')
    {
        number = number * 10 + (int)(givenString[*index] - '0');
        ++(*index);
    }
    return number;
}

bool isOperation(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

Node* addNodeRecursive(const char* givenString, int* index, bool* isWorking)
{
    if (!(*isWorking))
    {
        return NULL;
    }
    int stringSize = strlen(givenString);
    ++(*index);
    while (*index != stringSize && (givenString[*index] == ' ' || givenString[*index] == '(' || givenString[*index] == ')'))
    {
        ++(*index);
    }
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    if (isOperation(givenString[*index]))
    {
        newNode->operation = givenString[*index];
        newNode->leftSon = addNodeRecursive(givenString, index, isWorking);
        newNode->rightSon = addNodeRecursive(givenString, index, isWorking);
    }
    else
    {
        newNode->operand = numberConvert(givenString, index);
    }
    return newNode;
}

Tree* createAndAdd(char* givenString, bool* isWorking)
{
    Tree* tree = calloc(1, sizeof(Tree));
    if (tree == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    int index = -1;
    tree->root = addNodeRecursive(givenString, &index, isWorking);
    return tree;
}

int calculateRecursive(Node* node, bool* isWorking)
{
    if (node->leftSon == NULL && node->rightSon == NULL)
    {
        return node->operand;
    }
    const int operandFirst = calculateRecursive(node->leftSon, isWorking);
    const int operandSecond = calculateRecursive(node->rightSon, isWorking);
    switch (node->operation)
    {
    case '+':
        return operandFirst + operandSecond;
    case '-':
        return operandFirst - operandSecond;
    case '/':
    {
        if (operandSecond == 0)
        {
            *isWorking = false;
            return - 1;
        }
        return operandFirst / operandSecond;
    }
    default:
        return operandFirst * operandSecond;
    }
}

int doCalculation(Tree* tree, bool* isWorking)
{
    return calculateRecursive(tree->root, isWorking);
}

void printRecursive(Node* node)
{
    if (node->leftSon == NULL && node->rightSon == NULL)
    {
        printf("%d", node->operand);
        return;
    }
    printf("( %c ", node->operation);
    printRecursive(node->leftSon);
    printf(" ");
    printRecursive(node->rightSon);
    printf(" )");
}

void printTree(Tree* tree)
{
    if (isEmpty(tree))
    {
        return;
    }
    printRecursive(tree->root);
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
    return;
}