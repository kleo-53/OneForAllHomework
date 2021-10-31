#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "stackTests.h"

#define ARRAY_SIZE 40

bool isOperation(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int doСalculation(int first, int second, char symbol)
{
    switch (symbol)
    {
    case '+':
        return first + second;
    case '-':
        return second - first;
    case '*':
        return second * first;
    case '/':
        return second / first;
    default:
        return second + first;
    }
}

int runMainComputationProgram(StackElement** head, char* expression)
{
    char element = ' ';
    bool continueCalculations = true;
    char ch = ' ';
    int i = 0;
    while (continueCalculations)
    {
        element = expression[i];
        ch = expression[i + 1];
        if (ch == '\0')
        {
            continueCalculations = false;
        }
        if (isOperation(element))
        {
            if (isEmpty(*head))
            {
                return -1;
            }
            int first = pop(&*head);
            if (isEmpty(*head))
            {
                return -1;
            }
            int second = pop(&*head);
            push(&*head, doСalculation(first, second, element));
        }
        else
        {
            push(&*head, atoi(&element));
        }
        i += 2;
    }
    return 0;
}

bool testOperations()
{
    return isOperation('+') && isOperation('-') && isOperation('*') && isOperation('/');
}

bool testShortCorrectCase()
{
    StackElement* head = NULL;
    char expression[ARRAY_SIZE] = "1\0";
    const int result = runMainComputationProgram(&head, expression);
    if (result == -1)
    {
        return false;
    }
    int correctResult = 1;
    return head->value == correctResult;
}

bool testLongCorrectCase()
{
    StackElement* head = NULL;
    char expression[ARRAY_SIZE] = "1 2 6 + * 2 4 - /\0";
    const int result = runMainComputationProgram(&head, expression);
    if (result == -1)
    {
        return false;
    }
    int correctResult = -4;
    return head->value == correctResult;
}

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks() || !testOperations() || !testShortCorrectCase() || !testLongCorrectCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    StackElement* head = NULL;
    char expression[ARRAY_SIZE] = "";
    gets_s(expression, ARRAY_SIZE);
    const int result = runMainComputationProgram(&head, expression);
    if (result == -1)
    {
        printf("At some step there were too few variables in the stack, the program could not complete correctly :(");
        return -1;
    }
    printf("Result of calculations is %d", head->value);
    return 0;
}