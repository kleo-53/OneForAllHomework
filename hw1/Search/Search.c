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

void swap(int* first, int* second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
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
    const int p = partition(sortingArray, low, high);
    if (p > low)
    {
        myQsort(sortingArray, low, p - 1);
    }
    myQsort(sortingArray, p + 1, high);
}

bool binSearch(int* sortingArray, int leftElement, int rightElement, int needElement)
{
    while (leftElement + 1 < rightElement)
    { 
        const int middle = (leftElement + rightElement) / 2;
        if (sortingArray[middle] >= needElement)
        {
            rightElement = middle;
        }
        else
        {
            leftElement = middle;
        }
    }
    return sortingArray[leftElement] == needElement || sortingArray[rightElement] == needElement;
}

bool checkQSort(int* sortingArray, int* correctArray, int arraySize)
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

bool checkBinSearch(int* sortingArray, int* elements, int arraySize)
{
    for (int i = 0; i < arraySize / 2; ++i)
    {
        if (!binSearch(sortingArray, 0, arraySize, elements[i]))
        {
            return false;
        }
    }
    for (int i = arraySize / 2; i < arraySize; ++i)
    {
        if (binSearch(sortingArray, 0, arraySize, elements[i]))
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
    int elements[ARRAY_SIZE] = { -4, 0, -321, -42, 6, 111, -53, 5, 5, 0, 77, 78, 31, 329, 70, -2, 101, -44, -8, 48 };

    qsort(correctArray, ARRAY_SIZE, sizeof(int), comparator);
    myQsort(sortingArray, 0, ARRAY_SIZE - 1);
    return checkQSort(sortingArray, correctArray, ARRAY_SIZE) && checkBinSearch(sortingArray, elements, ARRAY_SIZE);
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
        printf("Size could not be negative. Please enter correct data.");
        return 1;
    }

    int* inputArray = (int*)calloc(arraySize, sizeof(int));
    if (inputArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }

    srand((unsigned int)time((time_t*)NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        inputArray[i] = randomElement;
        printf("%d ", inputArray[i]);
    }
    myQsort(inputArray, 0, arraySize - 1);

    int amountNumbers = 0;
    printf("\nEnter amount of elements to search: ");
    scanf("%d", &amountNumbers);

    for (int i = 0; i < amountNumbers; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        if (binSearch(inputArray, 0, arraySize, randomElement))
        {
            printf("\nNumber %d contains in array", randomElement);
        }
        else
        {
            printf("\nNumber %d not contains in array", randomElement);
        }
    }
    free(inputArray);
}
