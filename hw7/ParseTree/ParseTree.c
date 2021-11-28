#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"
#include "treeTests.h"

#define ARRAY_SIZE 50

int main()
{
    if (!testSmallCase() || !testBigCase() || !testWithoutBracketsCase() || !testIncorrectDividing())
    {
        printf("Tests failed:(");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Some errors have occured");
        return -1;
    }
    char givenString[ARRAY_SIZE] = "";
    fgets(givenString, ARRAY_SIZE, file);
    fclose(file);
    bool isWorking = true;
    Tree* tree = createAndAdd(givenString, &isWorking);
    if (!isWorking)
    {
        printf("some errors have occured");
        return -1;
    }
    printf("All data in tree:\n");
    printTree(tree);
    const int result = doCalculation(tree, &isWorking);
    if (isWorking)
    {
        printf("\nAnd calculations result is: %d", result);
    }
    else
    {
        printf("\nCannot be divided by zero!");
    }
    deleteTree(tree);
    return 0;
}