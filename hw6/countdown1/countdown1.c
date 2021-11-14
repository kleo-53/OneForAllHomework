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
        deleteList(list);
        return false;
    }
    isAdded = addElement(15, list);
    if (!isAdded)
    {
        deleteList(list);
        return false;
    }
    if (getRemaining(list) != 10)
    {
        deleteList(list);
        return false;
    }
    if (getLength(list) != 2)
    {
        deleteList(list);
        return false;
    }
    deleteElement(list);
    if (getLength(list) != 1)
    {
        deleteList(list);
        return false;
    }
    deleteElement(list);
    bool result = getLength(list) == 0;
    deleteList(list);
    return result;
}

bool testPassFunction()
{
    List* list = createList();
    bool isAdded = addElement(10, list);
    if (!isAdded)
    {
        deleteList(list);
        return false;
    }
    isAdded = addElement(15, list);
    if (!isAdded)
    {
        deleteList(list);
        return false;
    }
    if (getRemaining(list) != 10)
    {
        deleteList(list);
        return false;
    }
    passElement(list);
    if (getRemaining(list) != 15)
    {
        deleteList(list);
        return false;
    }
    deleteElement(list);
    passElement(list);
    if (getRemaining(list) != 10)
    {
        deleteList(list);
        return false;
    }
    deleteList(list);
    return true;
}

int doExecution(int countOfWarriors, int frequency)
{
    List* warriorsList = createList();
    for (int i = 1; i < countOfWarriors + 1; ++i)
    {
        bool isAdded = addElement(i, warriorsList);
        if (!isAdded)
        {
            deleteList(warriorsList);
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
        deleteList(warriorsList);
        return ERROR_VALUE;
    }
    deleteList(warriorsList);
    return result;
}

bool testWorkSix()
{
    List* warriorsList = createList();
    int result = doExecution(6, 3);
    deleteList(warriorsList);
    return result == 1 ? true : false;
}

bool testWorkOne()
{
    List* warriorsList = createList();
    int result = doExecution(1, 10);
    deleteList(warriorsList);
    return result == 1 ? true : false;
}

bool testWorkMany()
{
    List* warriorsList = createList();
    int result = doExecution(19, 31);
    deleteList(warriorsList);
    return result == 18 ? true : false;
}

int main()
{
    if (!testAddDeleteLengthFunctions() || !testPassFunction() || !testWorkSix() || !testWorkOne() || !testWorkMany())
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
    const int result = doExecution(countOfWarriors, frequency);
    printf(result == ERROR_VALUE ? "Some errors were occured" : "The warrior numbered %d will survive!", result);
    return 0;
}