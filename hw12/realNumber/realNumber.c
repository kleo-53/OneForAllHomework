#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 32

typedef enum State
{
    Start,
    SeenFirstDigit,
    SeenDot,
    SeenDigitAfterDot,
    SeenE,
    SeenDigitAfterE,
    SeenSign,
    ErrorString

} State;

bool isDigit(const char symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

char nextChar(const char* string, long long i)
{
    return string[i + 1];
}

bool isCorrectState(State state)
{
    return state == SeenFirstDigit || state == SeenDigitAfterDot || state == SeenDigitAfterE;
}

bool doLexer(char* string)
{
    State state = Start;
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
        case Start:
        {
            state = isDigit(c) ? SeenFirstDigit : ErrorString;
            break;
        }
        case SeenFirstDigit:
        {
            if (isDigit(c))
            {
                state = SeenFirstDigit;
            }
            else if (c == '.')
            {
                state = SeenDot;
            }
            else if (c == 'E')
            {
                state = SeenE;
            }
            else 
            {
                state = ErrorString;
            }
            break;
        }
        case SeenDot:
        {
            state = isDigit(c) ? SeenDigitAfterDot : ErrorString;
            break;
        }
        case SeenDigitAfterDot:
        {
            if (isDigit(c))
            {
                state = SeenDigitAfterDot;
            }
            else if (c == 'E')
            {
                state = SeenE;
            }
            else
            {
                state = ErrorString;
            }
            break;
        }
        case SeenE:
        {
            if (isDigit(c))
            {
                state = SeenDigitAfterE;
            }
            else if (c == '+' || c == '-')
            {
                state = SeenSign;
            }
            else
            {
                state = ErrorString;
            }
            break;
        }
        case SeenDigitAfterE:
        {
            state = isDigit(c) ? SeenDigitAfterE : ErrorString;
            break;
        }
        case SeenSign:
        {
            state = isDigit(c) ? SeenDigitAfterE : ErrorString;
            break;
        }
        default:
        {
            state = ErrorString;
            break;
        }
        }
    }
    return isCorrectState(state);
}

bool testCorrectCase()
{
    return doLexer("21") && doLexer("21.4") && doLexer("21.4E35") && doLexer("21.4E-55") &&
        doLexer("2342.4234E+999") && doLexer("21E48") && doLexer("21E-18");
}

bool testIncorrectCase()
{
    return doLexer("21.") || doLexer("23.43E") || doLexer("23.32E+") || doLexer("....") || 
        doLexer("234sdhfisuhg") || doLexer("21E");
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
    printf(doLexer(inputString) ? "Yes, it is a real number." : "No, it is not a real number.");
    return 0;
}