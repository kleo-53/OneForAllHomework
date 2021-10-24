#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

bool isOperation(char symbol)
{
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') ? true : false;
}

int calculator(int first, int second, char symbol)
{
    if (symbol == '+')
    {
        return first + second;
    }
    else if (symbol == '-')
    {
        return second - first;
    }
    else if (symbol == '*')
    {
        return second * first;
    }
    else
    {
        return second / first;
    }
}

bool testCorrectCase()
{
    StackElement* head = NULL;
    if (!isOperation('-'))
    {
        return false;
    }
    push(&head, 12);
    push(&head, 3);
    int first = pop(&head);
    int second = pop(&head);
    char symbol = '-';
    int result = calculator(first, second, symbol);
    if (first != 3 || second != 12 || result != 9) 
    {
        return false;
    }
    push(&head, result);
    push(&head, -3);
    symbol = '*';
    first = pop(&head);
    second = pop(&head);
    result = calculator(first, second, symbol);
    if (first != -3 || second != 9 || result != -27 || head != NULL)
    {
        return false;
    }
    return true;
}

int main()
{
    if (!testCorrectCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    StackElement* head = NULL;
    char element[5] = "";
    bool continueCalculations = true;
    char ch = ' ';
    while (continueCalculations)
    {
        scanf_s("%[^ \n]", &element, 4);
        scanf_s("%c", &ch, 1);
        if (ch == '\n')
        {
            continueCalculations = false;
        }
        if (isOperation(element[0]))
        {
            int first = pop(&head);
            if (!isEmpty(head))
            {
                int second = pop(&head);
                push(&head, calculator(first, second, element[0]));
            }
            else
            {
                printf("not enough variables!");
                return -1;
            }
        }
        else
        {
            push(&head, atoi(&element));
        }
    }
    printf("Result of calculations is %d", head->value);
    return 0;
}