#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool testCase() 
{
    FILE* oneNumberFile = fopen("g1.txt", "r");
    if (oneNumberFile == NULL) 
    {
        return false;
    }
    int controlNumber = 0;
    fscanf_s(oneNumberFile, "%d", &controlNumber);
    fclose(oneNumberFile);
    const int correctNumber = 37;
    if (controlNumber != correctNumber)
    {
        return false;
    }
    FILE* numbersFile = fopen("f1.txt", "r");
    if (numbersFile == NULL) 
    {
        return false;
    }
    FILE* output = fopen("h1.txt", "w");
    if (output == NULL) 
    {
        return false;
    }
    int inputNumber = 0;
    int correctInputNumbers[13] = { 1, 2, 3, 55, 3, 36, 37, 38, 894, 0, 1, 44, 33 };
    int correctPrintfNumbers[8] = { 1, 2, 3, 3, 36, 0, 1, 33 };
    int readLine = 0;
    int readCorrectLine = 0;
    while (!feof(numbersFile)) {
        fscanf_s(numbersFile, "%d", &inputNumber);
        if (inputNumber != correctInputNumbers[readLine])
        {
            fclose(numbersFile);
            fclose(output);
            return false;
        }
        if (inputNumber < controlNumber)
        {
            fprintf(output, "%d\n", inputNumber);
            if (inputNumber != correctPrintfNumbers[readCorrectLine])
            {
                fclose(numbersFile);
                fclose(output);
                return false;
            }
            ++readCorrectLine;
        }
        ++readLine;
    }
    fclose(numbersFile);
    fclose(output);
    return true;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failsed:(");
        return -1;
    }
    FILE* oneNumberFile = fopen("g.txt", "r");
    if (oneNumberFile == NULL) 
    {
        return -1;
    }
    int controlNumber = 0;
    fscanf_s(oneNumberFile, "%d", &controlNumber);
    fclose(oneNumberFile);

    FILE* numbersFile = fopen("f.txt", "r");
    if (numbersFile == NULL) 
    {
        return -1;
    }
    FILE* output = fopen("h.txt", "w");
    if (output == NULL) 
    {
        return -1;
    }
    int inputNumber = 0;
    while (!feof(numbersFile)) 
    {
        fscanf_s(numbersFile, "%d", &inputNumber);
        if (inputNumber < controlNumber)
        {
            fprintf(output, "%d\n", inputNumber);
        }
    }
    fclose(numbersFile);
    fclose(output);
}