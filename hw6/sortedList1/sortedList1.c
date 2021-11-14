#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int menu(List* myList)
{
    printf("\n0 - Finish work");
    printf("\n1 - Add data in sorted list");
    printf("\n2 - Delete data from sorted list");
    printf("\n3 - Print sorted list");
    printf("\nChose the command: ");

    char command = ' ';
    scanf_s("%c", &command, 2);
    switch (command)
    {
    case '0':
        return -1;
    case '1':
    {
        printf("Enter data: ");
        int data = 0;
        scanf_s("%d%*c", &data);
        bool isAdded = addData(myList, data);
        isAdded ? printf("The data %d added successfully!\n", data) : printf("Did not add data to list:(");
        break;
    }
    case '2':
    {
        printf("Enter data: ");
        int data = 0;
        scanf_s("%d%*c", &data);
        bool isDeleted = deleteData(myList, data);
        isDeleted ? printf("This data not in list!\n") : printf("The data %d deleted successfully!\n", data);
        break;
    }
    case '3':
    {
        scanf_s("%*c");
        if (isEmpty(myList))
        {
            printf("The list is empty!\n");
        }
        else
        {
            printf("There are all data in the list:\n");
            printList(myList);
            printf("\n");
        }
        break;
    }
    default:
        scanf_s("%*c");
        printf("No option selected\n");
    }
    return 0;
}

bool testAddData()
{
    List* myList = createList();
    bool isAdded = addData(myList, 10);
    if (!isAdded)
    {
        deleteList(myList);
        return false;
    }
    isAdded = addData(myList, 35);
    deleteList(myList);
    return isAdded;
}

bool testDeleteData()
{
    List* myList = createList();
    bool isAdded = addData(myList, 10);
    if (!isAdded)
    {
        deleteList(myList);
        return false;
    }
    bool isDeleted = deleteData(myList, 35);
    if (isDeleted)
    {
        deleteList(myList);
        return false;
    }
    isDeleted = deleteData(myList, 10);
    deleteList(myList);
    return isDeleted;
}

bool testWorkCase()
{
    List* myList = createList();
    bool isAdded = addData(myList, 10);
    isAdded = addData(myList, 11) && isAdded;
    isAdded = addData(myList, 1) && isAdded;
    isAdded = addData(myList, 843) && isAdded;
    isAdded = addData(myList, -5) && isAdded;
    if (!isAdded)
    {
        deleteList(myList);
        return false;
    }
    FILE* inFile = fopen("test.txt", "w");
    printListInFile(myList, inFile);
    fclose(inFile);
    char* fileString = calloc(40, sizeof(char));
    if (fileString == NULL)
    {
        deleteList(myList);
        return false;
    }
    FILE* outFile = fopen("test.txt", "r");
    fscanf_s(outFile, "%[^\n]s", fileString, 40);
    fclose(outFile);
    char* correctString = { "-5 1 10 11 843 " };
    if (strcmp(fileString, correctString) != 0)
    {
        deleteList(myList);
        return false;
    }
    bool isWorks = deleteData(myList, 11);
    isWorks = deleteData(myList, 1) && isWorks;
    if (!isWorks)
    {
        deleteList(myList);
        return false;
    }
    isAdded = addData(myList, -5);
    isAdded = addData(myList, 15) && isAdded;
    if (!isAdded)
    {
        deleteList(myList);
        return false;
    }
    FILE* inFile2 = fopen("test.txt", "w");
    printListInFile(myList, inFile2);
    fclose(inFile2);
    FILE* outFile2 = fopen("test.txt", "r");
    strcat(fileString, "");
    fscanf_s(outFile2, "%[^\n]s", fileString, 40);
    fclose(outFile2);
    correctString = "-5 -5 10 15 843 ";
    deleteList(myList);
    return strcmp(fileString, correctString) != 0 ? false : true;
}

int main()
{
    if (!testAddData() || !testDeleteData() || !testWorkCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    List* myList = createList();
    int result = menu(myList);
    while (result != -1)
    {
        result = menu(myList);
    }
    deleteList(myList);
    return 0;
}