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

int numberConvert(char* givenString, int* index)
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

Node* addNodeRecursive(char* givenString, int* index, bool isWork)
{
    if (!isWork)
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
        isWork = false;
        return NULL;
    }
    if (isOperation(givenString[*index]))
    {
        newNode->operation = givenString[*index];
        newNode->leftSon = addNodeRecursive(givenString, index, isWork);
        newNode->rightSon = addNodeRecursive(givenString, index, isWork);
    }
    else
    {
        newNode->operand = numberConvert(givenString, index);
    }
    return newNode;
}

Tree* createAndAdd(char* givenString, bool isWork)
{
    Tree* tree = calloc(1, sizeof(Tree));
    if (tree == NULL)
    {
        isWork = false;
        return NULL;
    }
    int index = -1;
    tree->root = addNodeRecursive(givenString, &index, isWork);
    return tree;
}

int calculateRecursive(Node* node)
{
    if (node->leftSon == NULL && node->rightSon == NULL)
    {
        return node->operand;
    }
    int operandFirst = calculateRecursive(node->leftSon);
    int operandSecond = calculateRecursive(node->rightSon);
    switch (node->operation)
    {
    case '+':
        return operandFirst + operandSecond;
    case '-':
        return operandFirst - operandSecond;
    case '*':
        return operandFirst * operandSecond;
    default:
        return operandFirst / operandSecond;;
    }
}

int doCalculation(Tree* tree)
{
    return calculateRecursive(tree->root);
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
    return;
}

void printTree(Tree* tree)
{
    if (isEmpty(tree))
    {
        return;
    }
    printRecursive(tree->root);
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
    free(node);
}

void deleteTree(Tree* tree)
{
    deleteChildren(tree->root);
    free(tree);
    return;
}