#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define ARRAY_SIZE 50

/*bool testCase()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWork = true;
    addValue(tree, 100, "root", isWork);
    addValue(tree, 50, "rootLSon", isWork);
    addValue(tree, 150, "rootRSon", isWork);
    addValue(tree, 25, "LLSon", isWork);
    addValue(tree, 75, "LRSon", isWork);
    addValue(tree, 120, "RLSon", isWork);
    addValue(tree, 250, "RRSon", isWork);
    addValue(tree, 111, "RLL", isWork);
    addValue(tree, 101, "root", isWork);
    if (!isWork || !inTree(tree, 120) || inTree(tree, 1) || strcmp("rootRSon", getValue(tree, 150)) != 0)
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, 101, "RLLL", isWork);
    if (!isWork || strcmp("RLLL", getValue(tree, 101)) != 0 || !inTree(tree, 101) || strcmp(getValue(tree, 1023), "err") != 0)
    {
        deleteTree(tree);
        return false;
    }
    deleteValue(tree, 101, isWork);
    deleteValue(tree, 120, isWork);
    deleteValue(tree, 50, isWork);
    deleteValue(tree, 100, isWork);
    deleteValue(tree, 150, isWork);
    if (!isWork || inTree(tree, 120) || !inTree(tree, 111) || !inTree(tree, 75) || inTree(tree, 100) || !inTree(tree, 25) || !inTree(tree, 250) || inTree(tree, 50))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}
*/
int main()
{
    /*if (!testCase())
    {
        printf("Tests failed:(");
        return -1;
    }*/
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