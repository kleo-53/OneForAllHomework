#include <stdio.h>
#define arraySize 40

int main()
{
    int size = 0;
    int massiv[arraySize];
    int element = 0;
    int counter = 0;

    printf("Enter a size of array: ");
    scanf("%d", &size);
    printf("Enter array elements: \n");

    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &massiv[i]);
        if (massiv[i] == 0)
        {
            ++counter;
        }
    }

    printf("This array has %d zero elements.\n", counter);
}
