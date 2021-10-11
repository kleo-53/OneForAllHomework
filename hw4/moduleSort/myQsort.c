#include "myQsort.h"

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
    const int position = partition(sortingArray, low, high);
    if (position > low)
    {
        myQsort(sortingArray, low, position - 1);
    }
    myQsort(sortingArray, position + 1, high);
}
