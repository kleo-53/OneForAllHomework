#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE 7
#define RANGE 101

int abs(const int* element)
{
    if (*element < 0)
    {
        return -*element;
    }
    return *element;
}

int summNumber(int number)
{
    int summ = 0;
    while (number > 0)
    {
        summ += number % 10;
        number /= 10;
    }
    return summ;
}

bool testCorrectCase()
{
    int randomArray[ARRAY_SIZE] = { -45, 9, 4, 2, 0, -52, 111114};
    int sumArray[ARRAY_SIZE] = { 9, 9, 4, 2, 0, 7, 9 };
    for (int i = 0; i  < ARRAY_SIZE; ++i)
    {
        if (summNumber(abs(&randomArray[i])) != sumArray[i])
        {
            return false;
        }
    }
    return true;
}

bool createArrayCheck(int* createArray)
{
    if (createArray == NULL)
    {
        printf("Calloc function broke :(");
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

    int arraySize = 0;
    printf("Enter size of array: ");
    scanf("%d", &arraySize);
    if (arraySize < 0)
    {
        printf("Size could not be negative. Please enter correct data.");
        return 1;
    }

    int* randomArray = (int*)calloc(arraySize, sizeof(int));
    if (!createArrayCheck(randomArray))
    {
        return -1;
    }

    srand((unsigned int)time(NULL));
    printf("Elements of array: \n");
    int* sumArray = (int*)calloc(arraySize, sizeof(int));
    if (!createArrayCheck(sumArray))
    {
        return -1;
    }

    int maxSum = 0;
    for (int i = 0; i < arraySize; ++i)
    {
        const int randomElement = -RANGE / 2 + rand() % RANGE;
        randomArray[i] = randomElement;
        printf("%d ", randomArray[i]);

        sumArray[i] = summNumber(abs(&randomElement));
        if (sumArray[i] > maxSum)
        {
            maxSum = sumArray[i];
        }
    }
    printf("\nThe highest sum of digits is %d. Elements with this sum: \n", maxSum);
    for (int i = 0; i < arraySize; ++i)
    {
        if (sumArray[i] == maxSum)
        {
            printf("%d ", randomArray[i]);
        }
    }

    free(randomArray);
    free(sumArray);
}
