#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define ARRAY_SIZE (sizeof(int) * 8) - 1
#define RANGE 1001

void addition(bool *firstNumber, bool *secondNumber, bool *additionNumber, int arraySize)
{

    bool overflow = false;
    for (int i = arraySize - 1; i > 0; --i)
    {
        if (firstNumber[i] && secondNumber[i])
        {
            additionNumber[i] = overflow;
            overflow = true;
        }
        else if (!firstNumber[i] && !secondNumber[i])
        {
            additionNumber[i] = overflow;
            overflow = false;
        }
        else
        {
            if (overflow)
            {
                additionNumber[i] = false;
                overflow = true;
            }
            else
            {
                additionNumber[i] = true;
                overflow = false;
            }
        }
    }
}

void printNumber(bool *number, int arraySize)
{
    for (int i = 0; i < arraySize; ++i) 
    {
        printf(number[i] ? "1" : "0");
    }
}

void binNumber(int x, bool* number, int arraySize) 
{
    int bit = 0b1000000000000000000000000000000;
    for (int j = 0; j < arraySize; ++j)
    {
        number[j] = ((x & bit) ? true : false);
        bit = bit >> 1;
    }
}

short int toDecimal(bool* number, int arraySize)
{
    short int decimal = 0;
    int bit = 0b1;
    for (int j = 0; j < arraySize; ++j)
    {
        decimal = ((number[arraySize - j - 1]) ? (decimal | bit) : decimal);
        bit = bit << 1;
    }
    return decimal;
}

bool compareNumbers(bool *number, bool *checkNumber)
{
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (number[i] != checkNumber[i])
        {
            return false;
        }
    }
    return true;
}

bool testCorrectCase()
{
    int zeroNumber = 0;
    int firstNumber = 194;
    int secondNumber = 832;
    int thirdNumber = -1025;

    bool zeroBinNumber[ARRAY_SIZE] = { false };
    binNumber(zeroNumber, zeroBinNumber, ARRAY_SIZE);
    bool checkZero[ARRAY_SIZE] = { false };
    if (!compareNumbers(zeroBinNumber, checkZero))
    {
        return false;
    }
    bool firstBinNumber[ARRAY_SIZE] = { false };
    binNumber(firstNumber, firstBinNumber, ARRAY_SIZE);
    bool checkFirst[ARRAY_SIZE] = { false };
    checkFirst[23] = true;
    checkFirst[24] = true;
    checkFirst[29] = true;
    if (!compareNumbers(firstBinNumber, checkFirst))
    {
        return false;
    }
    bool secondBinNumber[ARRAY_SIZE] = { false };
    binNumber(secondNumber, secondBinNumber, ARRAY_SIZE);
    bool checkSecond[ARRAY_SIZE] = { false };
    checkSecond[21] = true;
    checkSecond[22] = true;
    checkSecond[24] = true;
    if (!compareNumbers(secondBinNumber, checkSecond))
    {
        return false;
    }
    bool checkThird[ARRAY_SIZE] = { false };
    bool thirdBinNumber[ARRAY_SIZE] = { false };
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        checkThird[i] = true;
    }
    checkThird[20] = false;
    binNumber(thirdNumber, thirdBinNumber, ARRAY_SIZE);
    if (!compareNumbers(thirdBinNumber, checkThird))
    {
        return false;
    }
    bool summAll[ARRAY_SIZE] = { false };
    addition(firstBinNumber, secondBinNumber, summAll, ARRAY_SIZE);
    bool checkSumm[ARRAY_SIZE] = { false };
    checkSumm[20] = true;
    checkSumm[29] = true;
    if (!compareNumbers(summAll, checkSumm))
    {
        return false;
    }
    int checkDecimalSum = firstNumber + secondNumber;
    int decimalSum = toDecimal(summAll, ARRAY_SIZE);
    if (checkDecimalSum != decimalSum)
    {
        return false;
    }
    addition(zeroBinNumber, summAll, summAll, ARRAY_SIZE);
    if (!compareNumbers(summAll, checkSumm))
    {
        return false;
    }
    checkDecimalSum += zeroNumber;
    decimalSum = toDecimal(summAll, ARRAY_SIZE);
    if (checkDecimalSum != decimalSum)
    {
        return false;
    }
    addition(thirdBinNumber, summAll, summAll, ARRAY_SIZE);
    checkSumm[20] = false;
    checkSumm[29] = false;
    checkSumm[30] = true;
    if (!compareNumbers(summAll, checkSumm))
    {
        return false;
    }
    checkDecimalSum += thirdNumber;
    decimalSum = toDecimal(summAll, ARRAY_SIZE);
    if (checkDecimalSum != decimalSum)
    {
        return false;
    }
    return true;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    if (!testCorrectCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    printf("Введите два числа: ");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf_s("%d %d", &firstNumber, &secondNumber);

    bool firstBinNumber[ARRAY_SIZE] = { false };
    binNumber(firstNumber, firstBinNumber, ARRAY_SIZE);
    printf("Первое число в двоичной системе: \n");
    printNumber(firstBinNumber, ARRAY_SIZE);

    bool secondBinNumber[ARRAY_SIZE] = { false };
    binNumber(secondNumber, secondBinNumber, ARRAY_SIZE);
    printf("\nВторое число в двоичной системе: \n");
    printNumber(secondBinNumber, ARRAY_SIZE);
    
    bool summary[ARRAY_SIZE] = { false };
    addition(firstBinNumber, secondBinNumber, summary, ARRAY_SIZE);
    printf("\n\nСумма чисел в двоичной системе: \n");
    printNumber(summary, ARRAY_SIZE);

    printf("\nСумма чисел в десятичной системе:\n%d", toDecimal(summary, ARRAY_SIZE));
    return 0;
}