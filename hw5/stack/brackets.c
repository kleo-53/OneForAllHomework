#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "stackTests.h"

void checkEqual(StackElement** stack, char element)
{
    if (isEmpty(*stack) || element == '(' || element == '[' || element == '{')
    {
        push(stack, element);
        return;
    }
    else
    {
        char popElement = pop(stack);
        if ((popElement == '}' &&  element == '{') || (popElement == ']' && element == '[') || (popElement == ')' && element == '('))
        {
            push(stack, popElement);
            push(stack, element);
        }
    }
}

bool isBracket(char element)
{
    return element == '(' || element == ')' || element == '[' || element == ']' || element == '{' || element == '}';
}
int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks())
    {
        printf("Tests failed");
        return -1;
    }
    StackElement* head = NULL;
    char element = ' ';
    char ch = ' ';
    bool continueWork = true;
    while (continueWork)
    {
        scanf_s("%c", &element, 1);
        if (element == '\n')
        {
            continueWork = false;
        }
        else if (isBracket(element))
        {
            checkEqual(&head, element);
        }
    }
    if (isEmpty(head))
    {
        printf("This sequence is correct.");
    }
    else
    {
        printf("This sequence is not correct.");
    }
}