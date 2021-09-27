#include <stdio.h>
#include <time.h>
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

int comparator(const int* first, const int* second)
{
    return (*(int*)first - *(int*)second);
}

void insertionSort(int* Array, int low, int high)
{
    for (int j = low + 1; j <= high; ++j)
    {
        const int currentElement = Array[j];
        int i = j;
        for (i; i > low; --i)
        {
            if (currentElement < Array[i - 1])
            {
                Array[i] = Array[i - 1];
            }
            else
            {
                break;
            }
        }
        if (i != j)
        {
            Array[i] = currentElement;
        }
    }
}

int partition(int* randomArray, int low, int high)
{
    int pivot = randomArray[high];
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (randomArray[j] <= pivot)
        {
            swap(&randomArray[i], &randomArray[j]);
            ++i;
        }
    }
    swap(&randomArray[i], &randomArray[high]);
    return i;
}

void myQsort(int* randomArray, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    if (high - low < 10)
    {
        insertionSort(randomArray, low, high);
    }
    else
    {
        int p = partition(randomArray, low, high);
         if (p > low)
         {
            myQsort(randomArray, low, p - 1);
         }
         myQsort(randomArray, p + 1, high);
    }
}


bool testCorrectCase()
{
    int correctArray[ARRAYSIZE] = { 0 };
    int randomArray[ARRAYSIZE] = { 0 };
    srand((unsigned int)time((time_t)NULL));
    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        const int randomElement = -ARRAYSIZE / 2 + rand() % RANGE;
        correctArray[i] = randomElement;
        randomArray[i] = randomElement;
    }

    qsort(correctArray, ARRAYSIZE, sizeof(int), comparator);
    myQsort(randomArray, 0, ARRAYSIZE - 1);

    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        if (randomArray[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testEqualCase()
{
    int randomArray[ARRAYSIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };
    int correctArray[ARRAYSIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };

    myQsort(randomArray, 0, ARRAYSIZE - 1);
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
