#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../stack/stack.h"
#include "../stack/stackTests.h"

#define ARRAY_SIZE 40
bool smartAddElement(StackElement** stack, char element)
{
    if (element == '(' || element == '[' || element == '{')
    {
        bool isAdded = push(stack, element);
        return isAdded;
    }
    if (isEmpty(*stack))
    {
        return false;
    }
    char popElement = pop(stack);
    if ((popElement == '{' && element == '}') || (popElement == '[' && element == ']') || (popElement == '(' && element == ')'))
    {
        return true;
    }
    bool isAdded = push(stack, popElement);
    if (!isAdded)
    {
        return false;
    }
    isAdded = push(stack, element);
    return isAdded;
}

bool isBracket(char element)
{
    return element == '(' || element == ')' || element == '[' || element == ']' || element == '{' || element == '}';
}

bool menu(char* givenString, int stringSize)
{
    StackElement* head = NULL;
    char element = ' ';
    bool continueWork = true;
    int i = 0;
    while (i != stringSize)
    {
        element = givenString[i];
        if (isBracket(element))
        {
            bool isCorrect = smartAddElement(&head, element);
            if (!isCorrect)
            {
                return false;
            }
        }
        i += 1;
    }
    return isEmpty(head);
}

bool testIncorrectCase()
{
    char testString[5] = "({)}";
    return !menu(testString, 4);
}

bool testCorrectCase()
{
    char testString[17] = "({})[]((([]){}))";
    return menu(testString, 16);
}

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks() || !testIncorrectCase() || !testCorrectCase())
    {
        printf("Tests failed");
        return -1;
    }
    char element = ' ';
    int stringSize = 0;
    char inputString[ARRAY_SIZE] = { " " };
    bool continueWork = true;
    while (continueWork)
    {
        scanf_s("%c", &element, 1);
        if (element == '\n')
        {
            continueWork = false;
        }
        inputString[stringSize] = element;
        stringSize += 1;
    }
    if (menu(inputString, stringSize))
    {
        printf("This sequence is correct.");
    }
    else
    {
        printf("This sequence is not correct.");
    }
}