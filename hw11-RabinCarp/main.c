#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RabinCarp.h"
#define STR_SIZE 1000

bool testSimpleCase()
{
    char inputLine[30] = { "cadab" };
    FILE* file = fopen("test.txt", "r");
    if (file == NULL)
    {
        free(inputLine);
        return false;
    }
    char fileLine[STR_SIZE] = { " " };
    int numberLine = 1;
    while (!feof(file))
    {
        fgets(&fileLine, STR_SIZE, file);
        int resultRK = rabinKarp(fileLine, inputLine);
        if (numberLine == 1 && resultRK == 6)
        {
            fclose(file);
            return true;
        }
        ++numberLine;
    }
    fclose(file);
    return false;
}

bool testSmallCase()
{
    char inputLine[30] = { "ncarp" };
    FILE* file = fopen("test.txt", "r");
    if (file == NULL)
    {
        free(inputLine);
        return false;
    }
    char fileLine[STR_SIZE] = { " " };
    int numberLine = 1;
    while (!feof(file))
    {
        fgets(&fileLine, STR_SIZE, file);
        int resultRK = rabinKarp(fileLine, inputLine);
        if (numberLine == 2 && resultRK == 5)
        {
            fclose(file);
            return true;
        }
        ++numberLine;
    }
    fclose(file);
    return false;
}

bool testHardCase()
{
    char inputLine[30] = { "ada bra aa" };
    FILE* file = fopen("test.txt", "r");
    if (file == NULL)
    {
        free(inputLine);
        return false;
    }
    char fileLine[STR_SIZE] = { " " };
    int numberLine = 1;
    while (!feof(file))
    {
        fgets(&fileLine, STR_SIZE, file);
        int resultRK = rabinKarp(fileLine, inputLine);
        if (numberLine == 1 && resultRK == 20)
        {
            fclose(file);
            return true;
        }
        ++numberLine;
    }
    fclose(file);
    return false;
}


int main()
{
    if (!testSmallCase() || !testSimpleCase() || !testHardCase())
    {
        printf("Tests failed.");
        return 0;
    }
    printf("Enter text line:\n");
    char inputLine[STR_SIZE] = { " " };
    scanf_s("%[^\n]", &inputLine, STR_SIZE);

    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        free(inputLine);
        return -1;
    }
    char fileLine[STR_SIZE] = { " " };
    int numberLine = 1;
    while (!feof(file))
    {
        fgets(&fileLine, STR_SIZE, file);
        int resultRK = rabinKarp(fileLine, inputLine);
        if (resultRK != -1)
        {
            fclose(file);
            printf("This line first encountered in a file at line %d, position %d.", numberLine, resultRK);
            return 0;
        }
        ++numberLine;
    }
    fclose(file);
    printf("There is not such line in file:(");
    return 0;
}