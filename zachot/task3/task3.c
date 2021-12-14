#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32

bool isDigit(const char symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

char nextChar(const char* string, long long i)
{
    if (i + 1< (int)strlen(string))
    {
        return string[i + 1];
    }
    return '\0';
}

bool machine(char* string)
{
    int state = 0;
    int i = -1;
    while (true)
    {
        if (i == strlen(string))
        {
            break;
        }
        char c = nextChar(string, i);
        ++i;
        switch (state)
        {
        case 0:
        {
            state = (isDigit(c)) ? 1 : -1;
            break;
        }
        case 1:
        {
            state = (isDigit(c)) ? 2 : -1;
            break;
        }
        case 2:
        {
            state = (c == '.') ? 3 : -1;
            break;
        }
        case 3:
        {
            state = (c == 'B' || c == 'S' || c == 'M') ? 4 : -1;
            break;
        }
        case 4:
        {
            state = (isDigit(c)) ? 5 : -1;
            break;
        }
        case 5:
        {
            state = (isDigit(c)) ? 6 : -1;
            break;
        }
        case 6:
        {
            state = (c == '-') ? 7 : -1;
            break;
        }
        case 7:
        {
            state = (c == 'm') ? 8 : -1;
            break;
        }
        case 8:
        {
            state = (c == 'm') ? 9 : -1;
            break;
        }
        case 9:
        {
            state = (c == '\n' || c == '\0') ? 10 : -1;
            break;
        }
        default:
        {
            state = -1;
            break;
        }
        }
    }
    return state == 10;
}

bool testCorrectCase()
{
    return machine("21.B10-mm");
}

bool testIncorrectCase()
{
    return machine("234g") || machine("23.M-mm") || machine("23.32df") || machine("....");
}

int main()
{
    if (!testCorrectCase() || testIncorrectCase())
    {
        printf("Tests failed.");
        return -1;
    }
    char inputString[SIZE] = { "" };
    scanf_s("%s", &inputString, SIZE);
    printf(machine(inputString) ? "Yes, it is matmeh group." : "No, it is not matmeh group.");
    return 0;
}