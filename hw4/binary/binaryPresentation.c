#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define ARRAY_SIZE 16
#define RANGE 1001

int abs(int x) 
{
    return x > 0 ? x : -x;
}

void addition(bool *firstNumber, bool *secondNumber, bool *additionNumber)
{
    bool overflow = false;
    for (int i = ARRAY_SIZE - 1; i > 0; --i)
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

void subtractionOne(bool* subtractionNumber)
{
    bool overflow = true;
    bool number[ARRAY_SIZE] = { false };
    for (int i = ARRAY_SIZE - 1; i > -1; --i)
    {
        number[i] = subtractionNumber[i];
    }
    for (int i = ARRAY_SIZE - 1; i > 0; --i)
    {
        if (overflow)
        {
            if (number[i])
            {
                subtractionNumber[i] = false;
                overflow = false;
            }
            else
            {
                subtractionNumber[i] = true;
            }
        }
        else
        {
            subtractionNumber[i] = number[i];
        }
    }
}

void binNumber(int number, bool* binNumber)
{
    if (number >= 0)
    {
        binNumber[0] = false;
        int bit = 0b1;
        for (int i = ARRAY_SIZE - 1; i > 0; --i) 
        {
            binNumber[i] = ((number & bit) ? true : false);
            bit = bit << 1;
        }
    }
    else
    {
        bool reverseNumber[ARRAY_SIZE] = { false };
        reverseNumber[0] = true;
        binNumber[0] = true;
        number = -number;
        int bit = 0b1;
        for (int i = ARRAY_SIZE - 1; i > 0; --i) 
        {
            reverseNumber[i] = ((number & bit) ? false : true);
            bit = bit << 1;
        }
        bool one[ARRAY_SIZE] = { false };
        one[ARRAY_SIZE - 1] = true;
        addition(reverseNumber, one, binNumber);
    }
}

void printNumber(bool *number, int arraySize)
{
    for (int i = 0; i < arraySize; ++i) 
    {
        printf(number[i] ? "1" : "0");
    }
}

int fromBinToDecimal(bool *binNumber, int arraySize)
{
    int decimalNumber = 0;
    int coefficient = 1;
    if (!binNumber[0])
    {

        for (int i = arraySize - 1; i > 0; --i)
        {
            decimalNumber += coefficient * binNumber[i];
            coefficient *= 2;
        }
    }
    else
    {
        subtractionOne(binNumber);
        for (int i = 0; i < arraySize; ++i)
        {
            if (binNumber[i])
            {
                binNumber[i] = false;
            }
            else
            {
                binNumber[i] = true;
            }
        }
        for (int i = arraySize - 1; i > 0; --i)
        {
            decimalNumber += coefficient * binNumber[i];
            coefficient *= 2;
        }
        decimalNumber = -decimalNumber;
    }
    return decimalNumber;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    printf("Введите два числа: ");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf_s("%d %d", &firstNumber, &secondNumber);

    bool firstBinNumber[ARRAY_SIZE] = { false };
    binNumber(firstNumber, firstBinNumber);
    printf("Первое число в двоичной системе: \n");
    printNumber(firstBinNumber, ARRAY_SIZE);

    bool secondBinNumber[ARRAY_SIZE] = { false };
    binNumber(secondNumber, secondBinNumber);
    printf("\nВторое число в двоичной системе: \n");
    printNumber(secondBinNumber, ARRAY_SIZE);
    
    bool summary[ARRAY_SIZE] = { false };
    if (firstNumber + secondNumber < 0)
    {
        summary[0] = true;
    }
    addition(firstBinNumber, secondBinNumber, summary);
    printf("\n\nСумма чисел в двоичной системе: \n");
    printNumber(summary, ARRAY_SIZE);

    int decimalSummary = fromBinToDecimal(summary, ARRAY_SIZE);
    printf("\nСумма чисел в десятичной системе:\n%d", decimalSummary);
    return 0;
}
