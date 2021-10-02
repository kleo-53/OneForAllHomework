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

void frequentElementCheck(int* inputArray, int arraySize, int* maximumCounter, int* frequentElement)
{
    int currentCounter = 1;
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

bool qsortChesk(int* sortingArray, int* correctArray, int arraySize)
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
    if (!qsortChesk(sortingArray, correctArray, ARRAY_SIZE))
    {
        return false;
    }

    int maximumCounter = 1;
    int frequentElement = sortingArray[0];
    frequentElementCheck(sortingArray, ARRAY_SIZE, &maximumCounter, &frequentElement);
    return frequentElement == 5 || frequentElement == -4 || maximumCounter == 2;
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

    int* randomArray = (int*)calloc(arraySize, sizeof(int));
    if (randomArray == NULL)
    {
        printf("Calloc function broke :(");
        return -1;
    }

    srand((unsigned int)time((time_t)NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }
    myQsort(randomArray, 0, arraySize - 1);

    int maximumCounter = 1;
    int frequentElement = randomArray[0];
    frequentElementCheck(randomArray, arraySize, &maximumCounter, &frequentElement);
    printf("\nThe most common array element is %d. It occurs in an array %d times.", frequentElement, maximumCounter);

    free(randomArray);
}
