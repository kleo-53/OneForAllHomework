#include "myQsort.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define RANGE 11

int comparator(const int* first, const int* second)
{
    return *first - *second;
}

void frequentElementCheck(int* inputArray, int arraySize, int* maximumCounter, int* frequentElement)
{
    int currentCounter = 1;
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

bool qsortCheck(int* sortingArray, int* correctArray, int arraySize)
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (sortingArray[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testCorrectCase()
{
    int sortingArray[ARRAY_SIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int correctArray[ARRAY_SIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };

    qsort(correctArray, ARRAY_SIZE, sizeof(int), comparator);
    myQsort(sortingArray, 0, ARRAY_SIZE - 1);
    if (!qsortCheck(sortingArray, correctArray, ARRAY_SIZE))
    {
        return false;
    }

    int maximumCounter = 1;
    int frequentElement = sortingArray[0];
    frequentElementCheck(sortingArray, ARRAY_SIZE, &maximumCounter, &frequentElement);
    return frequentElement == 5 || frequentElement == -4 || maximumCounter == 2;
}

int main()
{
    if (!testCorrectCase())
    {
        printf("Tests failed.");
        return 1;
    }

    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("file not found!");
        return 1;
    }

    int arraySize = 0;
    fscanf(file, "%d", &arraySize);
    if (arraySize < 0)
    {
        printf("Size could not be negative. Please enter correct data.");
        return 1;
    }

    int* inputArray = (int*)calloc(arraySize, sizeof(int));
    if (inputArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }
    int currentElement = 0;
    while (!feof(file)) {
        fscanf(file, "%d", &inputArray[currentElement]);
        ++currentElement;
    }
    fclose(file);

    srand((unsigned int)time((time_t)NULL));
    myQsort(inputArray, 0, arraySize - 1);

    int maximumCounter = 1;
    int frequentElement = inputArray[0];
    frequentElementCheck(inputArray, arraySize, &maximumCounter, &frequentElement);
    printf("\nThe most common array element is %d. It occurs in an array %d times.", frequentElement, maximumCounter);

    free(inputArray);
}