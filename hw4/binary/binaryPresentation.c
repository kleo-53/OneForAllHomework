#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define ARRAY_SIZE 16
#define RANGE 1001

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

void printNumber(bool *number, int arraySize)
{
    for (int i = 0; i < arraySize; ++i) 
    {
        printf(number[i] ? "1" : "0");
    }
}

/*int fromBinToDecimal(bool* binNumber, int arraySize)
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
            binNumber[i] ? false : true;
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
*/

void binNumber(int x, bool* number) 
{
    int bit = 0b1000000000000000;
    for (int j = 0; j < 16; ++j)
    {
        number[j] = ((x & bit) ? true : false);
        bit = bit >> 1;
    }
}

int toDec(bool* number, int arraySize)
{
    int decimal = 0;
    int bit = 0b1;
    for (int j = 0; j < 16; ++j)
    {
        decimal = ((number[j]) ? (decimal | bit) : decimal);
        bit = bit << 1;
    }
    return decimal;
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
    addition(firstBinNumber, secondBinNumber, summary);
    printf("\n\nСумма чисел в двоичной системе: \n");
    printNumber(summary, ARRAY_SIZE);

    //const int decimalSummary = fromBinToDecimal(summary, ARRAY_SIZE);
    //printf("\nСумма чисел в десятичной системе:\n%d", decimalSummary);
    const int summ = firstNumber + secondNumber;
    printf("\nСумма чисел в десятичной системе:\n%d", summ);
    printf("\nА по новой функции: %d", toDec(firstBinNumber, ARRAY_SIZE));
    return 0;
}