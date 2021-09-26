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

bool binSearch(int* randomArray, int leftElement, int rightElement, int needElement)
{
    while (leftElement + 1 < rightElement) { //log(n)
        int middle = leftElement + (rightElement - leftElement) / 2;
        if (randomArray[middle] >= needElement)
        {
            rightElement = middle;
        }
        else
        {
            leftElement = middle;
        }
    }
    if (randomArray[leftElement] == needElement || randomArray[rightElement] == needElement)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool testCorrectCase()
{
    int randomArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int correctArray[ARRAYSIZE] = { -4, 3, 44, -321, -4, 40, 41, -42, -35, 6, 60, 79, -53, 5, 5, -5, 17, 111, 0, -9 };
    int elements[ARRAYSIZE] = { -4, 0, -321, -42, 6, 111, -53, 5, 5, 0, 77, 78, 31, 329, 70, -2, 101, -44, -8, 48 };

    qsort(correctArray, ARRAYSIZE, sizeof(int), comparator);
    myQsort(randomArray, 0, ARRAYSIZE - 1);

    for (int i = 0; i < ARRAYSIZE; ++i) //qsort check
    {
        if (randomArray[i] != correctArray[i])
        {
            return false; 
        }
    }
    for (int i = 0; i < ARRAYSIZE / 2; ++i) // binsearch check
    {
        if (!binSearch(randomArray, 0, ARRAYSIZE, elements[i]))
        {
            return false;
        }
    }
    for (int i = ARRAYSIZE / 2; i < ARRAYSIZE; ++i)
    {
        if (binSearch(randomArray, 0, ARRAYSIZE, elements[i]))
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

    int amountNumbers = 0;
    printf("\nEnter amount of elements to search: ");
    scanf("%d", &amountNumbers);

    for (int i = 0; i < amountNumbers; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        if (binSearch(randomArray, 0, arraySize, randomElement))
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