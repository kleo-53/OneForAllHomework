#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define RANGE 1001

void swap(int* first, int* second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
}

int comparator(const void* first, const void* second)
{
    return *(int*)first - *(int*)second;
}

void mySelectionSort(int* sortingArray, int arraySize)
{
    int minIndex = 0;
    for (int i = 0; i < arraySize - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < arraySize; j++) 
        {
            if (sortingArray[j] < sortingArray[minIndex])
                minIndex = j;
        }
        swap(&sortingArray[i], &sortingArray[minIndex]);
    }
}

bool checkEqual(int* sortingArray, int* correctArray, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
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
    int correctArray[ARRAY_SIZE] = { 0 };
    int randomArray[ARRAY_SIZE] = { 0 };
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        const int randomElement = -ARRAY_SIZE / 2 + rand() % RANGE;
        correctArray[i] = randomElement;
        randomArray[i] = randomElement;
    }

    qsort(correctArray, ARRAY_SIZE, sizeof(int), comparator);
    mySelectionSort(randomArray, ARRAY_SIZE);
    return checkEqual(randomArray, correctArray, ARRAY_SIZE);
}

bool testEqualCase()
{
    int randomArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };
    int correctArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };

    mySelectionSort(randomArray, ARRAY_SIZE);
    return checkEqual(randomArray, correctArray, ARRAY_SIZE);
}

int main()
{
    if (!testCorrectCase() || !testEqualCase())
    {
        printf("Tests failed.");
        return 1;
    }

    printf("Size of array = 10\n");
    printf("Enter elements of array: \n");
    const int arraySize = 10;
    int* inputArray = (int*)calloc(arraySize, sizeof(int));
    if (inputArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }
    int randomElement = 0;
    for (int i = 0; i < arraySize; ++i)
    {
        scanf("%d", &randomElement);
        inputArray[i] = randomElement;
    }

    mySelectionSort(inputArray, arraySize);
    printf("\nArray after using selection sort: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", inputArray[i]);
    }
    free(inputArray);
}