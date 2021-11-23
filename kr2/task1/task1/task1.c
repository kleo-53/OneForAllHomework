#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

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
    reverse(&myList);
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
    char* correctString = { "-5 843 1 11 10 " };
    if (strcmp(fileString, correctString) != 0)
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
    reverse(&myList);
    FILE* inFile2 = fopen("test.txt", "w");
    printListInFile(myList, inFile2);
    fclose(inFile2);
    FILE* outFile2 = fopen("test.txt", "r");
    strcat(fileString, "");
    fscanf_s(outFile2, "%[^\n]s", fileString, 40);
    fclose(outFile2);
    correctString = "15 -5 10 11 1 843 -5 ";
    deleteList(myList);
    return strcmp(fileString, correctString) == 0;
}

int main()
{
    if (!testWorkCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    List* myList = createList();
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return -1;
    }
    int inputNumber = 0;
    bool isWork = true;
    while (!feof(file)) {
        fscanf_s(file, "%d", &inputNumber);
        isWork = addData(myList, inputNumber);
        if (!isWork)
        {
            printf("Some errors were occured");
            return -1;
        }
    }
    fclose(file);
    printf("This is the given list:\n");
    printList(myList);
    reverse(&myList);
    printf("\nThis is the list after reversing:\n");
    printList(myList);
    deleteList(myList);
    return 0;
}