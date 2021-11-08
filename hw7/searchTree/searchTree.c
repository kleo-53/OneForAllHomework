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
        addValue(*tree, key, value);
        scanf_s("%*c");
        printf("\n");
        return true;
    }
    case '2':
    {
        printf("Enter key: ");
        scanf_s("%d%*c", &key);
        char value[ARRAY_SIZE] = "";
        strcat(value, getValue(*tree, key));
        printf(strcmp(value, "err") == 0 ? "There is not such value for this key\n" : "Value for this key is: %s\n", value);
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
        deleteValue(*tree, key);
        return true;
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
    addValue(tree, 100, "root");
    addValue(tree, 50, "rootLSon");
    addValue(tree, 150, "rootRSon");
    addValue(tree, 25, "LLSon");
    addValue(tree, 75, "LRSon");
    addValue(tree, 120, "RLSon");
    addValue(tree, 250, "RRSon");
    addValue(tree, 111, "RLL");
    addValue(tree, 101, "root");
    if (!inTree(tree, 120) || inTree(tree, 1) || strcmp("rootRSon", getValue(tree, 150)) != 0)
    {
        deleteTree(tree);
        return false;
    }
    addValue(tree, 101, "RLLL");
    if (strcmp("RLLL", getValue(tree, 101)) != 0 || !inTree(tree, 101))
    {
        deleteTree(tree);
        return false;
    }
    deleteValue(tree, 101);
    deleteValue(tree, 120);
    deleteValue(tree, 50);
    deleteValue(tree, 100);
    deleteValue(tree, 150);
    if (inTree(tree, 120) || !inTree(tree, 111) || !inTree(tree, 75) || inTree(tree, 100) || !inTree(tree, 25) || !inTree(tree, 250) || inTree(tree, 50))
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