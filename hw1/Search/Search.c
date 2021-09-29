#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define RANGE 11

int comparator(const int* first, const int* second)
{
    return (*first - *second);
}

void swap(int* first, int* second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
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
    const int p = partition(Array, low, high);
    if (p > low)
    {
        MyQsort(Array, low, p - 1);
    }
    MyQsort(Array, p + 1, high);
}

bool BinSearch(int* Array, int leftElement, int rightElement, int needElement)
{
    while (leftElement + 1 < rightElement)
    { //log(n)
        const int middle = (leftElement + rightElement) / 2;
        if (Array[middle] >= needElement)
        {
            rightElement = middle;
        }
        else
        {
            leftElement = middle;
        }
    }
    return Array[leftElement] == needElement || Array[rightElement] == needElement;
}

bool CheckQSort(int* Array, int* correctArray, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
    {
        if (Array[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

bool CheckBinSearch(int* Array, int* elements, int arraySize)
{
    for (int i = 0; i < arraySize / 2; ++i)
    {
        if (!BinSearch(Array, 0, arraySize, elements[i]))
        {
            return false;
        }
    }
    for (int i = arraySize / 2; i < arraySize; ++i)
    {
        if (BinSearch(Array, 0, arraySize, elements[i]))
        {
            return false;
        }
    }
    return true;
}

bool TestCorrectCase()
{
    int randomArray[ARRAY_SIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int correctArray[ARRAY_SIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int elements[ARRAY_SIZE] = { -4, 0, -321, -42, 6, 111, -53, 5, 5, 0, 77, 78, 31, 329, 70, -2, 101, -44, -8, 48 };

    qsort(correctArray, ARRAY_SIZE, sizeof(int), comparator);
    MyQsort(randomArray, 0, ARRAY_SIZE - 1);
    return CheckQSort(randomArray, correctArray, ARRAY_SIZE) && CheckBinSearch(randomArray, elements, ARRAY_SIZE);
}

int main()
{
    if (!TestCorrectCase())
    {
        printf("Tests failed.");
        return 1;
    }

    int arraySize = 0;
    printf("Enter size of array: ");
    scanf("%d", &arraySize);
    if (arraySize < 0)
    {
        printf("Size could not be negative. Please enter correct data.");
        return 1;
    }

    int* randomArray = (int*)calloc(arraySize, sizeof(int));
    if (randomArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }

    srand((unsigned int)time((time_t*)NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }
    MyQsort(randomArray, 0, arraySize - 1);

    int amountNumbers = 0;
    printf("\nEnter amount of elements to search: ");
    scanf("%d", &amountNumbers);

    for (int i = 0; i < amountNumbers; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        if (BinSearch(randomArray, 0, arraySize, randomElement))
        {
            printf("\nNumber %d contains in array", randomElement);
        }
        else
        {
            printf("\nNumber %d not contains in array", randomElement);
        }
    }
    free(randomArray);
}