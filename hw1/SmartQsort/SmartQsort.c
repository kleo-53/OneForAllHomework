#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define RANGE 1001

void swap(int* first, int* second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

int comparator(const int* first, const int* second)
{
    return (*first - *second);
}

void InsertionSort(int* Array, int low, int high)
{
    for (int j = low + 1; j <= high; ++j)
    {
        const int currentElement = Array[j];
        int i = j;
        for (; i > low; --i)
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

int partition(int* Array, int low, int high)
{
    const int pivot = Array[high];
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (Array[j] <= pivot)
        {
            swap(&Array[i], &Array[j]);
            ++i;
        }
    }
    swap(&Array[i], &Array[high]);
    return i;
}

void MyQsort(int* Array, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    if (high - low < 10)
    {
        InsertionSort(Array, low, high);
        return;
    }
    int p = partition(Array, low, high);
    if (p > low)
    {
        MyQsort(Array, low, p - 1);
    }
    MyQsort(Array, p + 1, high);

}

bool CheckEqual(int* Array, int* correctArray)
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (Array[i] != correctArray[i])
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
    MyQsort(randomArray, 0, ARRAY_SIZE - 1);
    return(CheckEqual(randomArray, correctArray));
}

bool testEqualCase()
{
    int randomArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };
    int correctArray[ARRAY_SIZE] = { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };

    MyQsort(randomArray, 0, ARRAY_SIZE - 1);
    return(CheckEqual(randomArray, correctArray));
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

    MyQsort(randomArray, 0, arraySize - 1);
    printf("\n\nArray after using smart kusort: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", randomArray[i]);
    }
    free(randomArray);
}