#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define ARRAY_SIZE 50

bool testCase()
{
    bool isWork = true;
    Tree* tree = createAndAdd("(* (+ 1 11) 2)", &isWork);
    if (isEmpty(tree) || !isWork)
    {
        deleteTree(tree);
        return false;
    }
    const int result = doCalculation(tree);
    int correctResult = 24;
    deleteTree(tree);
    return result == correctResult;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("some errors have occured");
        return -1;
    }
    char givenString[ARRAY_SIZE] = "";
    int index = 0;
    char currentSymbol = ' ';
    currentSymbol = fgetc(file);
    while (currentSymbol != EOF)
    {
        if (currentSymbol == '\n')
        {
            break;
        }
        givenString[index] = currentSymbol;
        ++index;
        currentSymbol = fgetc(file);
    }
    fclose(file);
    bool isWork = true;
    Tree* tree = createAndAdd(givenString, isWork);
    if (!isWork)
    {
        printf("some errors have occured");
        return -1;
    }
    printf("All data in tree:\n");
    printTree(tree);
    printf("\nAnd calculations result is: %d", doCalculation(tree));
    deleteTree(tree);
    return 0;
}