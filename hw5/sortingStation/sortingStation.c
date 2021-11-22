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

void doSorting(const char* givenString, char* resultString, bool* isWorks)
{
    StackElement* head = NULL;
    int newIndex = 0;
    int givenIndex = 0;
    const int strSize = strlen(givenString);
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
                const char topElement = pop(&head, isWorks);
                if (!isWorks)
                {
                    deleteStack(&head, isWorks);
                    return;
                }
                if (givePriority(topElement) < givePriority(element))
                {
                    bool isAdded = push(&head, topElement);
                    if (!isAdded)
                    {
                        deleteStack(&head, isWorks);
                        isWorks = false;
                        return;
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
                deleteStack(&head, isWorks);
                isWorks = false;
                return;
            }
        }
        else if (element == '(')
        {
            bool isAdded = push(&head, element);
            if (!isAdded)
            {
                deleteStack(&head, isWorks);
                isWorks = false;
                return;
            }
        }
        else if (element == ')')
        {
            while (!isEmpty(head))
            {
                char topElement = pop(&head, isWorks);
                if (!isWorks)
                {
                    deleteStack(&head, isWorks);
                    return;
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
        resultString[newIndex] = pop(&head, isWorks);
        if (!isWorks)
        {
            deleteStack(&head, isWorks);
            return;
        }
        ++newIndex;
    }
    deleteStack(&head, isWorks);
}

bool testCorrectCase()
{
    const char inputString[ARRAY_SIZE] = "(1 + 1)*2";
    char resultString[ARRAY_SIZE] = "";
    const char* correctString = { "11+2*" };
    bool isWorks = true;
    doSorting(inputString, resultString, &isWorks);
    return isWorks && !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

bool testEmptyCase()
{
    const char inputString[ARRAY_SIZE] = "()";
    char resultString[ARRAY_SIZE] = "";
    const char* correctString = { "" };
    bool isWorks = true;
    doSorting(inputString, resultString, &isWorks);
    return isWorks && !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

bool testLongCase()
{
    const char inputString[ARRAY_SIZE] = "1 + 3 *(7+2)/4";
    char resultString[ARRAY_SIZE] = "";
    const char* correctString = { "1372+*4/+" };
    bool isWorks = true;
    doSorting(inputString, resultString, &isWorks);
    return isWorks && !(resultString == ERROR_STRING) && strcmp(resultString, correctString) == 0;
}

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks() || !testCorrectCase() || !testEmptyCase() || !testLongCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    char inputString[40] = "";
    printf("Enter arithmetic expression in infix form:\n");
    scanf_s("%[^\n]s", &inputString, ARRAY_SIZE);
    char resultString[ARRAY_SIZE] = "";
    bool isWorks = true;
    doSorting(inputString, resultString, &isWorks);
    if (!isWorks)
    {
        printf("\nSome errors have occured.");
        return -1;
    }
    printf("\nThis arithmetic expression in postfix form:\n");
    for (int i = 0; i < (int)strlen(resultString); ++i)
    {
        printf("%c ", resultString[i]);
    }
    return 0;
}