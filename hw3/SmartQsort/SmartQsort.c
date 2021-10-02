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

int comparator(const int* first, const int* second)
{
    return *first - *second;
}

void insertionSort(int* sortingArray, int low, int high)
{
    for (int j = low + 1; j <= high; ++j)
    {
        const int currentElement = sortingArray[j];
        int i = j;
        for (; i > low; --i)
        {
            if (currentElement < sortingArray[i - 1])
            {
                sortingArray[i] = sortingArray[i - 1];
            }
            else
            {
                break;
            }
        }
        if (i != j)
        {
            sortingArray[i] = currentElement;
        }
    }
}

int partition(int* sortingArray, int low, int high)
{
    const int pivot = sortingArray[high];
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (sortingArray[j] <= pivot)
        {
            swap(&sortingArray[i], &sortingArray[j]);
            ++i;
        }
    }
    swap(&sortingArray[i], &sortingArray[high]);
    return i;
}

void myQsort(int* sortingArray, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    if (high - low < 10)
    {
        insertionSort(sortingArray, low, high);
        return;
    }
    int p = partition(sortingArray, low, high);
    if (p > low)
    {
        myQsort(sortingArray, low, p - 1);
    }
    myQsort(sortingArray, p + 1, high);
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
    srand((unsigned int)time((time_t*)NULL));
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        const int randomElement = -ARRAY_SIZE / 2 + rand() % RANGE;
        correctArray[i] = randomElement;
        randomArray[i] = randomElement;
    }

    qsort(correctArray, ARRAY_SIZE, sizeof(int), comparator);
    myQsort(randomArray, 0, ARRAY_SIZE - 1);
    return checkEqual(randomArray, correctArray, ARRAY_SIZE);
}

bool testEqualCase()
{
    int randomArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };
    int correctArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };

    myQsort(randomArray, 0, ARRAY_SIZE - 1);
    return checkEqual(randomArray, correctArray, ARRAY_SIZE);
}

int main()
{
    if (!testCorrectCase() || !testEqualCase())
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

    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }

    myQsort(randomArray, 0, arraySize - 1);
    printf("\n\nArray after using smart kusort: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", randomArray[i]);
    }
    free(randomArray);
}
