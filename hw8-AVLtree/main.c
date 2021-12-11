#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AVLtree.h"
#include "tests.h"

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
    char key[ARRAY_SIZE] = "";
    switch (command)
    {
    case '0':
        return false;
    case '1':
    {
        printf("Enter key: ");
        scanf_s("%s", &key, ARRAY_SIZE);
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
        scanf_s("%s%*c", &key, ARRAY_SIZE);
        bool isWorking = true;
        char *value = getValue(*tree, key, &isWorking);
        if (!isWorking)
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
        scanf_s("%s%*c", &key, ARRAY_SIZE);
        bool isWorking = true;
        printf(inTree(*tree, key, &isWorking) ? "This key exists in dictionary\n" : "This key does not exist in dictionary\n");
        return true;
    }
    case '4':
    {
        printf("Enter key: ");
        scanf_s("%s%*c", &key, ARRAY_SIZE);
        bool isWorking = true;
        bool result = true;
        if (!inTree(*tree, key, &isWorking))
        {
            printf("This key does not exist in dictionary\n");
            return isWorking;
        }
        deleteValue(*tree, key, &isWorking, &result);
        printf(!isWorking ? "Some errors have occured\n" : "This key deleted successfully\n");
        return isWorking;
    }
    default:
        printf("Invalid command\n");
        return true;
    }
}

int main()
{
    if (!testAddAndInCase() || !testDeleteAndInCase() || !testGetValueCase() || !testLeftRotation() || !testRightRotation())
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