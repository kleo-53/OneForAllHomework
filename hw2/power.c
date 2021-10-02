#include <stdio.h>
#include <time.h>
#include <stdbool.h>

long long powerFast(long int number, int power)
{
    if (power < 0)
    {
        return -10000000000;
    }
    else if (power == 0)
    {
        return 1;
    }

    if (power % 2 == 0)
    {
        return powerFast(number * number, power / 2);
    }
    return number * powerFast(number, power - 1);
}

long long powerIterative(long int number, int power)
{
    if (power < 0)
    {
        return -10000000000;
    }

    long long answer = 1;
    for (int i = 0; i < power; ++i)
    {
        answer *= number;
    }
    return answer;
}

bool testCorrectCaseSmall()
{
    return (powerFast(4, 3) == 64) && (powerIterative(4, 3) == 64);
}

bool testCorrectCaseNegativeSmall()
{
    return (powerFast(-3, 5) == -243) && (powerIterative(-3, 5) == -243);
}

bool testCorrectCaseNegativeBig()
{
    return (powerFast(-13, 8) == 815730721) && (powerIterative(-13, 8) == 815730721);
}

bool testCorrectCaseBig()
{
    return (powerFast(11, 11) == 285311670611) && (powerIterative(11, 11) == 285311670611);
}

bool testCorrectCaseBorderZero()
{
    return (powerFast(0, 0) == 1) && (powerIterative(0, 0) == 1);
}

bool testCorrectCaseBorder1()
{
    return (powerFast(0, 30) == 0) && (powerIterative(0, 30) == 0);
}

bool testCorrectCaseBorder2()
{
    return (powerFast(80, 0) == 1) && (powerIterative(80, 0) == 1);
}

bool testIncorrectCase()
{
    return (powerFast(26, -3) == -10000000000) && (powerIterative(26, -3) == -10000000000);
}

int main()
{
    if (!testCorrectCaseSmall() || !testCorrectCaseNegativeSmall() || !testCorrectCaseNegativeBig() || !testCorrectCaseBig() ||
        !testCorrectCaseBorder1() || !testCorrectCaseBorder2() || !testCorrectCaseBorderZero() || !testIncorrectCase())
    {
        printf("Tests failed.\n");
        return 1;
    }

    long int number = 0;
    int power = 0;
    printf("Enter the number and the power:");
    scanf("%d %d", &number, &power);

    if (power < 0)
    {
        printf("This program cannot raise a number to a negative power. Please enter correct data.");
        return 1;
    }

    clock_t startRec = 0;
    clock_t stopRec = 0;
    startRec = clock();
    printf("Answer from fast power function: %lld\n", powerFast(number, power));
    stopRec = clock();
    printf("Fast recursive function works: %ld milliseconds.\n\n", (stopRec - startRec) * 1000 / CLK_TCK);

    clock_t startIter = 0;
    clock_t stopIter = 0;
    startIter = clock();
    printf("Answer from iterative power function: %lld\n", powerIterative(number, power));
    stopIter = clock();
    printf("Iterative function works: %ld milliseconds.\n", (stopIter - startIter) * 1000 / CLK_TCK);
}
