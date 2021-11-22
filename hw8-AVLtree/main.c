#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "AVLtree.h"

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
        bool isWork = true;
        addValue(*tree, key, value, &isWork);
        scanf_s("%*c");
        printf("\n");
        if (!isWork)
        {
            printf("Some errors have occured");
        }
        return isWork;
    }
    case '2':
    {
        printf("Enter key: ");
        scanf_s("%d%*c", &key);
        bool isWork = true;
        char *value = getValue(*tree, key, &isWork);
        if (!isWork)
        {
            printf("Some errors have occured");
            return false;
        }
        printf(value == NULL ? "There is not such value for this key\n" : "Value for this key is: %s\n", value);
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
        scanf_s("%d%*c", &key);
        bool isWork = true;
        bool result = true;
        if (!inTree(*tree, key))
        {
            printf("This key does not exist in dictionary\n");
            return isWork;
        }
        deleteValue(*tree, key, &isWork, &result);
        printf(!isWork ? "Some errors have occured\n" : "This key deleted successfully\n");
        return isWork;
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
    bool isWork = true;
    addValue(tree, 100, "root", &isWork);
    addValue(tree, 50, "rootLSon", &isWork);
    addValue(tree, 150, "rootRSon", &isWork);
    addValue(tree, 25, "LLSon", &isWork);
    addValue(tree, 75, "LRSon", &isWork);
    addValue(tree, 120, "RLSon", &isWork);
    addValue(tree, 250, "RRSon", &isWork);
    addValue(tree, 111, "RLL", &isWork);
    addValue(tree, 101, "root", &isWork);
    char* value = getValue(tree, 150, &isWork);
    if (!isWork || !inTree(tree, 120) || inTree(tree, 1) || value == NULL || strcmp("rootRSon", value) != 0)
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, 101, "RLLL", &isWork);
    char* value2 = getValue(tree, 101, &isWork);
    char* value3 = getValue(tree, 1023, &isWork);
    if (!isWork || value2 == NULL|| strcmp("RLLL", value2) != 0 || !inTree(tree, 101) || value3 != NULL)
    {
        deleteTree(tree);
        return false;
    }
    bool result = true;
    deleteValue(tree, 101, &isWork, &result);
    result = true;
    deleteValue(tree, 120, &isWork, &result);
    result = true;
    deleteValue(tree, 50, &isWork, &result);
    result = true;
    deleteValue(tree, 100, &isWork, &result);
    result = true;
    deleteValue(tree, 150, &isWork, &result);
    if (!isWork || inTree(tree, 120) || !inTree(tree, 111) || !inTree(tree, 75) || inTree(tree, 100) || !inTree(tree, 25) || !inTree(tree, 250) || inTree(tree, 50))
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