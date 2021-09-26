#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define strSize 40

int fibonacciRecursive(int number)
{
    if (number < 0)
    {
        return -1;
    }
    else if (number == 0 || number == 1)
    {
        return 1;
    }
    return fibonacciRecursive(number - 1) + fibonacciRecursive(number - 2);
}

int fibonacciIterative(int number)
{
    if (number < 0)
    {
        return -1;
    }

    int fibonacciPrevious = 1;
    int fibonacciCurrent = 1;
    int i = 2;
    int fibonacciNext = 0;

    while (i <= number)
    {
        fibonacciNext = fibonacciPrevious + fibonacciCurrent;
        fibonacciPrevious = fibonacciCurrent;
        fibonacciCurrent = fibonacciNext;
        ++i;
    }
    return fibonacciCurrent;
}

bool testCorrectCaseSmall()
{
    return (fibonacciRecursive(4) == 5) && (fibonacciIterative(4) == 5);
}

bool testCorrectCaseBig()
{
    return (fibonacciRecursive(40) == 165580141) && (fibonacciIterative(40) == 165580141);
}

bool testCorrectCaseBorder()
{
    return (fibonacciRecursive(0) == 1) && (fibonacciIterative(0) == 1);
}

bool testIncorrectCase() 
{
    return (fibonacciRecursive(-7) == -1) && (fibonacciIterative(-7) == -1);
}

int main()
{
    if (!testCorrectCaseSmall() || !testCorrectCaseBig() || !testCorrectCaseBorder() || !testIncorrectCase())
    {
        printf("Tests failed.\n");
        return 1;
    }

    int number = 0;
    printf("Enter number of the Fibonacci number:");
    scanf("%d", &number);

    clock_t startRec = clock();
    long long answer = fibonacciRecursive(number);
    if (answer == -1) {
        printf("Cannot display the Fibonacci number with a negative number. Please enter correct data.");
        return 1;
    }
    printf("Answer from recursive Fibonacci function: %ld\n", answer);
    clock_t stopRec = clock();
    printf("Recursive function works: %ld milliseconds.\n\n", (stopRec - startRec) * 1000 / CLK_TCK);

    clock_t startIter = clock();
    printf("Answer from iterative Fibonacci function: %d\n", fibonacciIterative(number));
    clock_t stopIter = clock();
    printf("Iterative function works: %ld milliseconds.\n", (stopIter - startIter) * 1000 / CLK_TCK);
}