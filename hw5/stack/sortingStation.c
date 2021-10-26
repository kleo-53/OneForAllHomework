#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "stackTests.h"

bool isBracket(char element)
{
    return element == '(' || element == ')' || element == '[' || element == ']' || element == '{' || element == '}';
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
    else if (operation == '(')
    {
        return 0;
    }
    else
    {
        return 2;
    }
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
    bool continueWork = true;
    while (continueWork)
    {
        scanf_s("%c", &element, 1);
        if (element == '\n')
        {
            continueWork = false;
        }
        else if (isDigit(element))
        {
            printf("%c ", element);
        }
        else if (isOperation(element))
        {
            while (!isEmpty(head))
            {
                char topElement = pop(&head);
                if (givePriority(topElement) < givePriority(element))
                {
                    push(&head, topElement);
                    break;
                }
                else
                {
                    printf("%c ", topElement);
                }
            }
            push(&head, element);
        }
        else if (element == '(')
        {
            push(&head, element);
        }
        else if (element == ')')
        {
            while (!isEmpty(head))
            {
                char topElement = pop(&head);
                if (topElement == '(')
                {
                    break;
                }
                else {
                    printf("%c ", topElement);
                }
                
            }
        }
    }
    while (!isEmpty(head))
    {
        printf("%c", pop(&head));
    }
}