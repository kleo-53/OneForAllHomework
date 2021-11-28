#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "..\stack\stack.h"
#include "..\stack\stackTests.h"

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

int compute(const char* expression, bool* isWorks)
{
    StackElement* head = NULL;
    bool continueCalculations = true;
    int i = 0;
    while (continueCalculations)
    {
        const char element = expression[i];
        if (expression[i + 1] == '\0')
        {
            continueCalculations = false;
        }
        if (isOperation(element))
        {
            if (isEmpty(head))
            {
                *isWorks = false;
                deleteStack(&head, isWorks);
                return -1;
            }
            const int first = pop(&head, isWorks);
            if (isEmpty(head) || !isWorks)
            {
                *isWorks = false;
                deleteStack(&head, isWorks);
                return -1;
            }
            const int second = pop(&head, isWorks);
            bool isAdded = push(&head, doСalculation(first, second, element));
            if (!isAdded || !isWorks)
            {
                *isWorks = false;
                deleteStack(&head, isWorks);
                return -1;
            }
        }
        else
        {
            bool isAdded = push(&head, atoi(&element));
            if (!isAdded)
            {
                *isWorks = false;
                deleteStack(&head, isWorks);
                return -1;
            }
        }
        i += 2;
    }
    if (head != NULL && head->next == NULL)
    {
        int result = head->value;
        deleteStack(&head, isWorks);
        return isWorks ? result : -1;
    }
    deleteStack(&head, isWorks);
    *isWorks = false;
    return -1;
}

bool testShortCorrectCase()
{
    char expression[ARRAY_SIZE] = "1"; 
    int correctResult = 1;
    bool isWorks = true;
    const int result = compute(expression, &isWorks);
    return isWorks && result == correctResult;
}

bool testLongCorrectCase()
{
    char expression[ARRAY_SIZE] = "1 2 6 + * 2 4 - /\0";
    int correctResult = -4;
    bool isWorks = true;
    const int result = compute(expression, &isWorks);
    return isWorks && result == correctResult;
}

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks() || !testShortCorrectCase() || !testLongCorrectCase())
    {
        printf("Tests failed:(");
        return -1;
    }
    printf("Enter data in reverse Polish notation:\n");
    char expression[ARRAY_SIZE] = "";
    gets_s(expression, ARRAY_SIZE);
    bool isWorks = true;
    const int result = compute(expression, &isWorks);
    if (!isWorks)
    {
        printf("At some step there were too few variables in the stack, the program could not complete correctly :(");
        return -1;
    }
    printf("Result of calculations is %d", result);
    return 0;
}