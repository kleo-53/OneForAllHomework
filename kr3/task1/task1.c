#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

bool testWorkCase()
{
    List* myList = createList(3, 5);
    bool isWorking = addData(myList, 9);
    isWorking = addData(myList, 9) && isWorking;
    isWorking = addData(myList, 8) && isWorking;
    isWorking = addData(myList, 6) && isWorking;
    isWorking = addData(myList, 5) && isWorking;
    isWorking = addData(myList, 4) && isWorking;
    isWorking = addData(myList, 3) && isWorking;
    isWorking = addData(myList, 3) && isWorking;
    isWorking = addData(myList, 1) && isWorking;
    isWorking = addData(myList, -3) && isWorking;
    if (!isWorking)
    {
        deleteList(myList);
        return false;
    }
    FILE* output = fopen("test.txt", "w");
    if (output == NULL)
    {
        deleteList(myList);
        return -1;
    }
    printListInFile(myList, output);
    fclose(output);
    deleteList(myList);
    FILE* testFile = fopen("test.txt", "r");
    char* testString = malloc(sizeof(char));
    if (testFile == NULL || testString == NULL)
    {
        fclose(testFile);
        free(testString);
        return false;
    }
    fgets(testString, 42, testFile);
    fclose(testFile);
    return strcmp(testString, "1 -3 5 4 3 3 9 9 8 6 ") == 0;
}

int main()
{
    if (!testWorkCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    int inputNumberA = 0;
    int inputNumberB = 0;
    int inputNumber = 0;
    bool isWorking = true;
    printf("Enter a and b:\n");
    scanf_s("%d", &inputNumberA);
    scanf_s("%d", &inputNumberB);
    List* myList = createList(inputNumberA, inputNumberB);
    FILE* file = fopen("f.txt", "r");
    if (file == NULL)
    {
        deleteList(myList);
        return -1;
    }
    while (!feof(file))
    {
        fscanf_s(file, "%d", &inputNumber);
        isWorking = addData(myList, inputNumber);
        if (!isWorking)
        {
            printf("Some errors were occured");
            deleteList(myList);
            fclose(file);
            return -1;
        }
    }
    fclose(file);
    FILE* output = fopen("g.txt", "w");
    if (file == NULL)
    {
        deleteList(myList);
        return -1;
    }
    printListInFile(myList, output);
    fclose(output);
    deleteList(myList);
    return 0;
}