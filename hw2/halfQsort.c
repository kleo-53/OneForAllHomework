#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAYSIZE 20
#define RANGE 1001

void swap(int* first, int* second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

void halfkusort(int* randomArray, size_t randomArraySize)
{
    int leftBorder = 0;
    int rightBorder = randomArraySize - 1;

    while (leftBorder < rightBorder)
    {
        if (randomArray[leftBorder + 1] >= randomArray[leftBorder])
        {
            while (randomArray[rightBorder] >= randomArray[leftBorder] && rightBorder > leftBorder)
            {
                --rightBorder;
            }
            if (rightBorder == leftBorder)
            {
                break;
            }
            swap(&randomArray[rightBorder], &randomArray[leftBorder + 1]);
        }
        swap(&randomArray[leftBorder + 1], &randomArray[leftBorder]);
        ++leftBorder;
    }
}

bool testCase(int randomArray[], int correctArray[])
{
    halfkusort(randomArray, ARRAYSIZE);
    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        if (randomArray[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int testArray[ARRAYSIZE] = { 6, 9, 3, 5, 632, 5, 211, 3, 2, 6, 55, 5, 490, 3, 4, 2, 100, 4, 56, 32 };
    int correctArray[ARRAYSIZE] = { 4, 3, 5, 2, 5, 4, 3, 2, 3, 5, 6, 55, 490, 6, 211, 632, 100, 9, 56, 32 }; 
    int equalArray[ARRAYSIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };

    if (!testCase(testArray, correctArray) || !testCase(equalArray, equalArray))
    {
        printf("Tests failed.");
        return 1;
    }

    int arraySize = 0;
    printf("Enter size of array: ");
    scanf("%d", &arraySize);

    if (arraySize < 0)
    {
        printf("Size cannot be negative. Please enter correct data.");
        return 1;
    }

    int* randomArray = (int*)calloc(arraySize, sizeof(int));
    if (randomArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }

    srand(time(NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }

    halfkusort(randomArray, arraySize);
    printf("\n\nArray after using halfkusort: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", randomArray[i]);
    }
    free(randomArray);
}
