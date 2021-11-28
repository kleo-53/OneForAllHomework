#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "tree.h"

#define ARRAY_SIZE 50

int menu(Tree** tree)
{
    printf("Choose a command:\n");
    printf("0 - Finish programm\n");
    printf("1 - Add value by key\n");
    printf("2 - Get value by key\n");
    printf("3 - Check if key in dictionary\n");
    printf("4 - Delete key and value\n");
    char command = '0';
    scanf_s("%c", &command, 2);
    int key = 0;
    switch (command)
    {
    case '0':
        return false;
    case '1':
    {
        printf("Enter key: ");
        scanf_s("%d", &key);
        printf("Enter value: ");
        char value[ARRAY_SIZE] = "";
        scanf_s("%s", &value, ARRAY_SIZE);
        bool isWorking = true;
        addValue(*tree, key, value, &isWorking);
        scanf_s("%*c");
        printf("\n");
        if (!isWorking)
        {
            printf("Some errors have occured");
        }
        return isWorking;
    }
    case '2':
    {
        printf("Enter key: ");
        scanf_s("%d%*c", &key);
        if (getValue(*tree, key) == NULL)
        {
            printf("There is not such value for this key\n");
        }
        else
        {
            char value[ARRAY_SIZE] = "";
            strcpy(value, getValue(*tree, key));
            printf("Value for this key is: %s\n", value);
        }
        return true;
    }
    case '3':
    {
        printf("Enter key: ");
        scanf_s("%d%*c", &key);
        printf(inTree(*tree, key) ? "This key exists in dictionary\n" : "This key does not exist in dictionary\n");
        return true;
    }
    case '4':
    {
        printf("Enter key: ");
        scanf_s("%d", &key);
        bool isWorking = true;
        deleteValue(*tree, key, &isWorking);
        if (!isWorking)
        {
            printf("Some errors have occured");
        }
        return isWorking;
    }
    default:
        printf("Invalid command\n");
        return true;
    }
}

bool testCase()
{
    Tree* tree = createTree();
    if (!isEmpty(tree))
    {
        deleteTree(tree);
        return false;
    }
    bool isWorking = true;
    addValue(tree, 100, "root", &isWorking);
    addValue(tree, 50, "rootLSon", &isWorking);
    addValue(tree, 150, "rootRSon", &isWorking);
    addValue(tree, 25, "LLSon", &isWorking);
    addValue(tree, 75, "LRSon", &isWorking);
    addValue(tree, 120, "RLSon", &isWorking);
    addValue(tree, 250, "RRSon", &isWorking);
    addValue(tree, 111, "RLL", &isWorking);
    addValue(tree, 101, "root", &isWorking);
    if (!isWorking || !inTree(tree, 120) || inTree(tree, 1) || strcmp("rootRSon", getValue(tree, 150)) != 0)
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, 101, "RLLL", &isWorking);
    if (!isWorking || strcmp("RLLL", getValue(tree, 101)) != 0 || !inTree(tree, 101) || getValue(tree, 1023) != NULL)
    {
        deleteTree(tree);
        return false;
    }
    deleteValue(tree, 101, &isWorking);
    deleteValue(tree, 120, &isWorking);
    deleteValue(tree, 50, &isWorking);
    deleteValue(tree, 100, &isWorking);
    deleteValue(tree, 150, &isWorking);
    if (!isWorking || inTree(tree, 120) || !inTree(tree, 111) || !inTree(tree, 75) || inTree(tree, 100) || !inTree(tree, 25) || !inTree(tree, 250) || inTree(tree, 50))
    {
        deleteTree(tree);
        return false;
    }
    deleteTree(tree);
    return true;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failed:(");
        return -1;
    }

    bool continueRunning = true;
    Tree* tree = createTree();
    while (continueRunning)
    {
        continueRunning = menu(&tree);
    }
    deleteTree(tree);
    return 0;
}