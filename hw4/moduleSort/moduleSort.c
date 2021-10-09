#pragma warning (disable : 6031)

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myQsort.h"
#include "qsortTests.h"

#define ARRAY_SIZE 20
#define RANGE 11

#define _CRT_DEFINE_NO_WARNINGS

void frequentElementCheck(int* inputArray, int arraySize, int* maximumCounter, int* frequentElement)
{
    int currentCounter = 1;
    *maximumCounter = 0;
    for (int i = 1; i < arraySize; ++i)
    {
        if (inputArray[i - 1] != inputArray[i])
        {
            if (currentCounter > *maximumCounter)
            {
                *maximumCounter = currentCounter;
                currentCounter = 1;
                *frequentElement = inputArray[i - 1];
            }
        }
        else
        {
            ++currentCounter;
        }
    }
    if (currentCounter > *maximumCounter)
    {
        *maximumCounter = currentCounter;
        *frequentElement = inputArray[arraySize - 1];
    }
}

int main()
{
    if (!testCorrectCase())
    {
        printf("Tests failed.");
        return 1;
    }

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) 
    {
        printf("file not found!");
        return 1;
    }

    int arraySize = 0;
    fscanf(file, "%d", &arraySize);
    if (arraySize < 0)
    {
        printf("Size could not be negative. Please enter correct data.");
        fclose(file);
        return 1;
    }

    int* inputArray = (int*)calloc(arraySize, sizeof(int));
    if (inputArray == NULL)
    {
        printf("Calloc function broke :(");
        fclose(file);
        return -1;
    }
    int currentElement = 0;
    while (!feof(file)) 
    {
        fscanf(file, "%d", &inputArray[currentElement]);
        ++currentElement;
    }
    fclose(file);
    myQsort(inputArray, 0, arraySize - 1);

    int maximumCounter = 1;
    int frequentElement = inputArray[0];
    frequentElementCheck(inputArray, arraySize, &maximumCounter, &frequentElement);
    printf("The most common array element in file is %d. It occurs in an array %d times.", frequentElement, maximumCounter);

    free(inputArray);
}
