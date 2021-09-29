#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAYSIZE 20
#define RANGE 11

int comparator(const int* first, const int* second)
{
    return (*first - *second);
}

void swap(int* first, int* second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

int partition(int* Array, int low, int high)
{
    int pivot = Array[high];
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

void FrequentElementCheck(int* Array, int arraySize, int* maximumCounter, int* frequentElement)
{
    int currentCounter = 1;
    for (int i = 1; i < arraySize; ++i)
    {
        if (Array[i - 1] != Array[i])
        {
            if (currentCounter > *maximumCounter)
            {
                *maximumCounter = currentCounter;
                currentCounter = 1;
                *frequentElement = Array[i - 1];
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
        *frequentElement = Array[arraySize - 1];
    }
}

bool TestCorrectCase()
{
    int randomArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int correctArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };

    qsort(correctArray, ARRAYSIZE, sizeof(int), comparator);
    MyQsort(randomArray, 0, ARRAYSIZE - 1);

    for (int i = 0; i < ARRAYSIZE; ++i) //qsort check
    {
        if (randomArray[i] != correctArray[i])
        {
            return false;
        }
    }

    int maximumCounter = 1;
    int frequentElement = randomArray[0];
    FrequentElementCheck(randomArray, ARRAYSIZE, &maximumCounter, &frequentElement);
    return frequentElement == 5 || frequentElement == -4 || maximumCounter == 2;
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

    srand((unsigned int)time((time_t)NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }
    MyQsort(randomArray, 0, arraySize - 1);

    int maximumCounter = 1;
    int frequentElement = randomArray[0];
    FrequentElementCheck(randomArray, arraySize, &maximumCounter, &frequentElement);
    printf("\nThe most common array element is %d. It occurs in an array %d times.", frequentElement, maximumCounter);

    free(randomArray);
}
