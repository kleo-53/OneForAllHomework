#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

#define ERROR_VALUE -1000007

bool testAddDeleteLengthFunctions()
{
    List* list = createList();
    bool isAdded = addElement(10, list);
    if (!isAdded)
    {
        return false;
    }
    isAdded = addElement(15, list);
    if (!isAdded)
    {
        return false;
    }
    if (getRemaining(list) != 10)
    {
        return false;
    }
    if (getLength(list) != 2)
    {
        return false;
    }
    deleteElement(list);
    if (getLength(list) != 1)
    {
        return false;
    }
    deleteElement(list);
    return getLength(list) == 0;
}

bool testPassFunction()
{
    List* list = createList();
    bool isAdded = addElement(10, list);
    if (!isAdded)
    {
        return false;
    }
    isAdded = addElement(15, list);
    if (!isAdded)
    {
        return false;
    }
    if (getRemaining(list) != 10)
    {
        return false;
    }
    passElement(list);
    if (getRemaining(list) != 15)
    {
        return false;
    }
    deleteElement(list);
    passElement(list);
    if (getRemaining(list) != 10)
    {
        return false;
    }
    deleteElement(list);
    return true;
}

int execution(int countOfWarriors, int frequency)
{
    List* warriorsList = createList();
    for (int i = 1; i < countOfWarriors + 1; ++i)
    {
        bool isAdded = addElement(i, warriorsList);
        if (!isAdded)
        {
            return ERROR_VALUE;
        }
    }
    while (getLength(warriorsList) != 1)
    {
        for (int i = 0; i < frequency - 1; ++i)
        {
            passElement(warriorsList);
        }
        deleteElement(warriorsList);
    }
    int result = getRemaining(warriorsList);
    if (result == -1)
    {
        return ERROR_VALUE;
    }
    deleteElement(warriorsList);
    return result;
}

bool testWork()
{
    int countOfWarriors = 6;
    int frequency = 3;
    List* warriorsList = createList();
    return execution(countOfWarriors, frequency) == 1;
}

int main()
{
    if (!testAddDeleteLengthFunctions() || !testPassFunction() || !testWork())
    {
        printf("Tests failed:(");
        return -1;
    }
    printf("Enter the number of warriors: ");
    int countOfWarriors = 0;
    scanf_s("%d", &countOfWarriors);
    printf("Enter the frequency of killing warriors: ");
    int frequency = 0;
    scanf_s("%d", &frequency);
    int result = execution(countOfWarriors, frequency);
    printf("The warrior numbered %d will survive!", result);
    return 0;
}