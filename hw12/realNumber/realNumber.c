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
    if (i + 1 < (int)strlen(string))
    {
        return string[i + 1];
    }
    return '\0';
}

bool isCorrectState(int state)
{
    return state == 1 || state == 3 || state == 5 || state == 7;
}

bool machine(char* string)
{
    int state = 0;
    int i = -1;
    while (true)
    {
        if (i == strlen(string) - 1)
        {
            break;
        }
        char c = nextChar(string, i);
        ++i;
        switch (state)
        {
        case 0:
        {
            state = isDigit(c) ? 1 : -1;
            break;
        }
        case 1:
        {
            if (isDigit(c))
            {
                state = 1;
            }
            else if (c == '.')
            {
                state = 2;
            }
            else 
            {
                state = -1;
            }
            break;
        }
        case 2:
        {
            state = isDigit(c) ? 3 : -1;
            break;
        }
        case 3:
        {
            if (isDigit(c))
            {
                state = 3;
            }
            else if (c == 'E')
            {
                state = 4;
            }
            else
            {
                state = -1;
            }
            break;
        }
        case 4:
        {
            if (isDigit(c))
            {
                state = 5;
            }
            else if (c == '+' || c == '-')
            {
                state = 6;
            }
            else
            {
                state = -1;
            }
            break;
        }
        case 5:
        {
            state = isDigit(c) ? 5 : -1;
            break;
        }
        case 6:
        {
            state = isDigit(c) ? 7 : -1;
            break;
        }
        case 7:
        {
            state = isDigit(c) ? 7 : -1;
            break;
        }
        default:
        {
            state = -1;
            break;
        }
        }
    }
    return isCorrectState(state);
}

bool testCorrectCase()
{
    return machine("21") && machine("21.4") && machine("21.4E35") && machine("21.4E-55") && machine("2342.4234E+999");
}

bool testIncorrectCase()
{
    return machine("21.") || machine("23.43E") || machine("23.32E+") || machine("....") || machine("234sdhfisuhg");
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
    printf(machine(inputString) ? "Yes, it is a real number." : "No, it is not a real number.");
    return 0;
}