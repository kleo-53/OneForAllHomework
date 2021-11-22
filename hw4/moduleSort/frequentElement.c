#include "frequentElement.h"
#include <stdbool.h>

#define ARRAY_SIZE 20

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

bool testFrequentCase()
{
    int sortingArray[ARRAY_SIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };

    int maximumCounter = 1;
    int frequentElement = sortingArray[0];
    frequentElementCheck(sortingArray, ARRAY_SIZE, &maximumCounter, &frequentElement);
    return frequentElement == 5 || frequentElement == -4 || maximumCounter == 2;
}