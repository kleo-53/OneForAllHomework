﻿#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myQsort.h"
#include "qsortTests.h"
#include "frequentElement.h"

#define ARRAY_SIZE 20
#define RANGE 11


int main()
{
    if (!testCorrectCase() || !testFrequentCase())
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
    fscanf_s(file, "%d", &arraySize);
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
        fscanf_s(file, "%d", &inputArray[currentElement]);
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
