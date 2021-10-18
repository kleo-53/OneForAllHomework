#include "qsortTests.h"
#include <stdbool.h>
#include <stdlib.h>
#include "myQsort.h"

#define ARRAY_SIZE 20

int comparator(const int* first, const int* second)
{
    return *first - *second;
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