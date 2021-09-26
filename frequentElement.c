#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAYSIZE 20
#define RANGE 11

int comparator(const int* first, const int* second)
{
    return (*(int*)first - *(int*)second);
}

void swap(int* first, int* second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
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
    if (low < high)
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
    int randomArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int correctArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };

    qsort(correctArray, ARRAYSIZE, sizeof(int), comparator);
    myQsort(randomArray, 0, ARRAYSIZE - 1);

    for (int i = 0; i < ARRAYSIZE; ++i) //qsort check
    {
        if (randomArray[i] != correctArray[i])
        {
            return false; 
        }
    }

    int maximumCounter = 1;
    int frequentElement = randomArray[0];
    int currentCounter = 1;
    for (int i = 1; i < ARRAYSIZE; ++i) //frequent element check
    {
        if (randomArray[i - 1] != randomArray[i])
        {
            if (currentCounter > maximumCounter)
            {
                maximumCounter = currentCounter;
                currentCounter = 1;
                frequentElement = randomArray[i - 1];
            }
        }
        else
        {
            ++currentCounter;
        }
    }
    if (currentCounter > maximumCounter)
    {
        maximumCounter = currentCounter;
        frequentElement = randomArray[ARRAYSIZE - 1];
    }
    if ((frequentElement != 5 && frequentElement != -4) && (maximumCounter != 2)) 
    {
        return false;
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

    const int arraySize = 0;
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

    srand(time(NULL));
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
    int currentCounter = 1;
    for (int i = 1; i < arraySize; ++i)
    {
        if (randomArray[i - 1] != randomArray[i])
        {
            if (currentCounter > maximumCounter)
            {
                maximumCounter = currentCounter;
                currentCounter = 1;
                frequentElement = randomArray[i - 1];
            }
        }
        else
        {
            ++currentCounter;
        }
    }
    if (currentCounter > maximumCounter)
    {
        maximumCounter = currentCounter;
        frequentElement = randomArray[arraySize - 1];
    }
    printf("\nThe most common array element is %d. It occurs in an array %d times.", frequentElement, maximumCounter);

    free(randomArray);
}