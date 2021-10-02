#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAYSIZE 10
#define RANGE 100001

int comparator(const int* first, const int* second)
{
    return (*first - *second);
}

void bubbleSort(int* bubbleArray, int bubbleArraySize)
{

    for (int i = 0; i < bubbleArraySize - 1; ++i)
    {
        for (int j = bubbleArraySize - 1; j > i; --j)
        {
            if (bubbleArray[j - 1] > bubbleArray[j])
            {
                const int temporaryElement = bubbleArray[j - 1];
                bubbleArray[j - 1] = bubbleArray[j];
                bubbleArray[j] = temporaryElement;
            }
        }
    }
}

bool countSort(int* countArray, int countArraySize)
{
    int minimumElement = countArray[0];
    int maximumElement = countArray[0];
    for (int i = 0; i < countArraySize; ++i)
    {
        if (minimumElement > countArray[i])
        {
            minimumElement = countArray[i];
        }
        if (maximumElement < countArray[i])
        {
            maximumElement = countArray[i];
        }
    }
    const int difference = maximumElement - minimumElement + 1;
    int* counterNumbers = (int*)calloc(difference, sizeof(int));
    if (counterNumbers == NULL)
    {
        printf("Calloc function broke :(");
        return false;
    }

    for (int i = 0; i < countArraySize; ++i)
    {
        ++counterNumbers[countArray[i] - minimumElement];
    }
    for (int i = 0, j = 0; i < difference; ++i)
    {
        for (; counterNumbers[i] > 0; --counterNumbers[i])
        {
            countArray[j] = i + minimumElement;
            ++j;
        }
    }
    free(counterNumbers);
    return true;
}

bool testCorrectCase()
{
    int correctArray[ARRAYSIZE] = { 0 };
    int bubbleArray[ARRAYSIZE] = { 0 };
    int countArray[ARRAYSIZE] = { 0 };

    srand((unsigned int)time((time_t)NULL));
    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        const int randomElement = -ARRAYSIZE / 2 + rand() % RANGE; // заполняем массивы случайными числами от -50000 до 50000
        correctArray[i] = randomElement;
        countArray[i] = randomElement;
        bubbleArray[i] = randomElement;
    }

    qsort(correctArray, ARRAYSIZE, sizeof(int), comparator);
    bubbleSort(bubbleArray, ARRAYSIZE);
    countSort(countArray, ARRAYSIZE);

    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        if (bubbleArray[i] != correctArray[i] || countArray[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    if (!testCorrectCase())
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

    int* bubbleArray = (int*)calloc(arraySize, sizeof(int));
    int* countArray = (int*)calloc(arraySize, sizeof(int));
    if (bubbleArray == NULL || countArray == NULL)
    {
        free(bubbleArray);
        free(countArray);
        printf("Calloc function broke :(");
        return -1;
    }

    int currentElement = 0;
    printf("Enter elements of array: ");

    for (int i = 0; i < arraySize; ++i)
    {
        scanf("%d", &currentElement);
        bubbleArray[i] = currentElement;
        countArray[i] = currentElement;
    }

    const clock_t startRec = clock();
    bubbleSort(bubbleArray, arraySize);
    const clock_t stopRec = clock();
    printf("Fast recursive function works: %ld milliseconds.\n", (stopRec - startRec) * 1000 / CLK_TCK);

    printf("Array after using bubble sort: ");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", bubbleArray[i]);
    }
    free(bubbleArray);

    const clock_t startIter = clock();
    countSort(countArray, arraySize);
    const clock_t stopIter = clock();
    printf("\nIterative function works: %ld milliseconds.\n", (stopIter - startIter) * 1000 / CLK_TCK);

    printf("Array after using count sort: ");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", countArray[i]);
    }
    free(countArray);
}
