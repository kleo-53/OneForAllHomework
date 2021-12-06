#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../stack/stack.h"
#include "../stack/stackTests.h"

#define ARRAY_SIZE 40

bool isOpeningBracket(const char element)
{
    return element == '(' || element == '[' || element == '{';
}

bool iClosingBracket(char element)
{
    return element == ')' || element == ']' || element == '}';
}

bool smartAddElement(StackElement** stack, char element)
{
    if (isOpeningBracket(element))
    {
        return push(stack, element);
    }
    if (isEmpty(*stack))
    {
        return false;
    }
    bool isWorks = true;
    char popElement = pop(stack, &isWorks);
    return isWorks & (popElement == '{' && element == '}') || (popElement == '[' && element == ']') || (popElement == '(' && element == ')');
}

bool isBracket(const char element)
{
    return isOpeningBracket(element) || iClosingBracket(element);
}

bool isSequenceCorrect(const char* givenString)
{
    StackElement* head = NULL;
    char element = ' ';
    bool isWorks = true;
    int i = 0;
    const int stringSize = strlen(givenString);
    while (i != stringSize)
    {
        element = givenString[i];
        if (isBracket(element))
        {
            bool isCorrect = smartAddElement(&head, element);
            if (!isCorrect)
            {
                deleteStack(&head, &isWorks);
                return false;
            }
        }
        ++i;
    }
    bool result = isEmpty(head);
    deleteStack(&head, &isWorks);
    return result;
}

bool testIncorrectCase()
{
    char testString[5] = "({)}";
    char testString2[3] = ")(";
    return !isSequenceCorrect(testString) && !isSequenceCorrect(testString2);
}

bool testCorrectCase()
{
    char testString[17] = "({})[]((([]){}))";
    return isSequenceCorrect(testString);
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
    printf("Enter a sequence of brackets: \n");
    scanf_s("%[^\n]s", &inputString, ARRAY_SIZE);
    if (isSequenceCorrect(inputString))
    {
        printf("This sequence is correct.");
    }
    else
    {
        printf("This sequence is not correct.");
    }
}