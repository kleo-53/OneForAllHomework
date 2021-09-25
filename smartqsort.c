#include <stdio.h>
#include <stdbool.h>

#define ARRAYSIZE 20
#define RANGE 1001

void insertionSort(int randomArray[], int low, int high)
{
    for (int i = low; i < high; ++i)
    {
        int currentElement = randomArray[i];
        int position = i - 1;
        while (position >= 0 && randomArray[position] > currentElement)
        {
            randomArray[position + 1] = randomArray[position];
            --position;
        }
        randomArray[position + 1] = currentElement;
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
            const int temporaryElement = randomArray[i];
            randomArray[i] = randomArray[j];
            randomArray[j] = temporaryElement;
            ++i;
        }
        const int temporaryElement = randomArray[i];
        randomArray[i] = randomArray[high];
        randomArray[high] = temporaryElement;
    }
    return i;
}

void qsort(int* randomArray, int low, int high)
{
    if (low < high)
    {
        int p = partition(randomArray, low, high);
        if (p - low < 10)
        {
            insertionSort(randomArray, low, p);
        }
        else
        {
            if (p > low)
            {
                qsort(randomArray, low, p - 1);
            }
        }

        if (high - p < 10)
        {
            insertionSort(randomArray, p, high + 1);
        }
        else
        {
            qsort(randomArray, p, high);
        }
    }
}

bool testCorrectCase()
{
    int randomArray[ARRAYSIZE] = { 6, -15, 433, -4, -4, -4, 543, 5, -9, 0, 33, -1, 42, 11, 8, 4, -79, 10, -3, -20 };
    int correctArray[ARRAYSIZE] = { -79, -20, -15, -9, -4, -4, -4, -3, -1, 0, 4, 5, 6, 8, 10, 11, 33, 42, 433, 543 };

    qsort(randomArray, 0, ARRAYSIZE - 1);
    for (int i = 0; i < ARRAYSIZE; ++i)
    {
        if (randomArray[i] != correctArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testMostlyEqualCase()
{
    int randomArray[ARRAYSIZE] = { -5, -5, -5, -6, -5, -5, -5, -5, -4, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5 };
    int correctArray[ARRAYSIZE] = { -6, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -4 };

    qsort(randomArray, 0, ARRAYSIZE - 1);
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
    if (!testCorrectCase() || !testMostlyEqualCase())
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

    srand(time(NULL));
    printf("Elements of array: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);
    }

    qsort(randomArray, 0, arraySize - 1);
    printf("\n\nArray after using smart kusort: \n");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", randomArray[i]);
    }
    free(randomArray);
}

/*
#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int ar[1010];
    for (int i = 0; i < n; ++i) {
        std::cin >> ar[i];
    }
    int l = 0;
    int r = n - 1;
    int need;
    std::cin >> need;
    while (l + 1 < r) {//log(n)
        int med = l + (r - l) / 2;
        if (ar[med] >= need) r = med;
        else l = med;
    }
    if (ar[l] == need || ar[r] == need) std::cout << "Number " << need << " contains in array";
    else std::cout << "Number " << need << " not contains in array";
}
*/
