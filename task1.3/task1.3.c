#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE 20

bool testCase()
{
    FILE* file = fopen("inputTest.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    char correctComments[6][ARRAY_SIZE] = { "" };
    strcpy(correctComments[0], "; comment");
    strcpy(correctComments[1], ";23");
    strcpy(correctComments[2], ";");
    strcpy(correctComments[3], ";t 34t ;223");
    int index = 0;
    int indexJ = 0;
    char currernSymbol = fgetc(file);
    while (currernSymbol != EOF)
    {
        if (currernSymbol == ';')
        {
            while (currernSymbol != EOF && currernSymbol != '\n')
            {
                if (currernSymbol != correctComments[index][indexJ])
                {
                    fclose(file);
                    return false;
                }
                currernSymbol = fgetc(file);
                ++indexJ;
            }
            indexJ = 0;
            ++index;
        }
        else
        {
            currernSymbol = fgetc(file);
        }
    }
    fclose(file);
    return true;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return -1;
    }
    char currernSymbol = fgetc(file);
    while (currernSymbol != EOF)
    {
        if (currernSymbol == ';')
        {
            while (currernSymbol != EOF && currernSymbol != '\n')
            {
                printf("%c", currernSymbol);
                currernSymbol = fgetc(file);
            }
            printf("\n");
        }
        else
        {
            currernSymbol = fgetc(file);
        }
    }
    fclose(file);
    return 0;
}