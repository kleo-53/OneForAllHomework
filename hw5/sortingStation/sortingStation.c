#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../stack/stack.h"
#include "../stack/stackTests.h"

#define ARRAY_SIZE 40
#define ERROR_STRING "err"

bool isBracket(char element)
{
    return element == '(' || element == ')';
}

bool isOperation(char element)
{
    return element == '+' || element == '-' || element == '*' || element == '/';
}

bool isDigit(char element)
{
    return (int)element - '0' >= 0 && (int)element - '0' <= 9;
}

int givePriority(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    return operation == '(' ? 0 : 2;
}

char* menu(char* givenString)
{
    StackElement* head = NULL;
    int newIndex = 0;
    int givenIndex = 0;
    char resultString[ARRAY_SIZE] = "";
    bool isWorks = true;
    int strSize = strlen(givenString);
    while (givenIndex != strSize)
    {
        char element = givenString[givenIndex];
        if (isDigit(element))
        {
            resultString[newIndex] = element;
            ++newIndex;
        }
        else if (isOperation(element))
        {
            while (!isEmpty(head))
            {
                char topElement = pop(&head, &isWorks);
                if (!isWorks)
                {
                    return ERROR_STRING;
                }
                if (givePriority(topElement) < givePriority(element))
                {
                    bool isAdded = push(&head, topElement);
                    if (!isAdded)
                    {
                        return ERROR_STRING;
                    }
                    break;
                }
                else
                {
                    resultString[newIndex] = topElement;
                    ++newIndex;
                }
            }
            bool isAdded = push(&head, element);
            if (!isAdded)
            {
                return ERROR_STRING;
            }
        }
        else if (element == '(')
        {
            bool isAdded = push(&head, element);
            if (!isAdded)
            {
                return ERROR_STRING;
            }
        }
        else if (element == ')')
        {
            while (!isEmpty(head))
            {
                char topElement = pop(&head, &isWorks);
                if (!isWorks)
                {
                    return ERROR_STRING;
                }
                if (topElement == '(')
                {
                    break;
                }
                else
                {
                    resultString[newIndex] = topElement;
                    ++newIndex;
                }
            }
        }
        ++givenIndex;
    }
    while (!isEmpty(head))
    {
        resultString[newIndex] = pop(&head, &isWorks);
        if (!isWorks)
        {
            return ERROR_STRING;
        }
        ++newIndex;
    }
    return resultString;
}

bool testCorrectCase()
{
    char inputString[ARRAY_SIZE] = "(1 + 1)*2";
    char resultString[ARRAY_SIZE] = "";
    const char correctString[ARRAY_SIZE] = "11+2*";
    strcat(resultString, menu(inputString));
    return !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

bool testEmptyCase()
{
    char inputString[ARRAY_SIZE] = "()";
    char resultString[ARRAY_SIZE] = "";
    const char correctString[ARRAY_SIZE] = "";
    strcat(resultString, menu(inputString));
    return !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

bool testLongCase()
{
    char inputString[ARRAY_SIZE] = "1 + 3 *(7+2)/4";
    char resultString[ARRAY_SIZE] = "";
    const char correctString[ARRAY_SIZE] = "1372+*4/+";
    strcat(resultString, menu(inputString));
    return !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks() || !testCorrectCase() || !testEmptyCase() || !testLongCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    char element = ' ';
    bool continueWork = true;
    char inputString[40] = "";
    int index = 0;
    scanf_s("%[^\n]s", &inputString, ARRAY_SIZE);
    char resultString[ARRAY_SIZE] = "";
    strcat(resultString, menu(inputString));
    if (resultString == ERROR_STRING)
    {
        printf("Some errors have occured.");
        return -1;
    }
    for (int i = 0; i < (int)strlen(resultString); ++i)
    {
        printf("%c ", resultString[i]);
    }
    return 0;
}