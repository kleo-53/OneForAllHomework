#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"

typedef enum SortKey
{
    name,
    phone
} SortKey;

void moveElements(List* listFrom, List* listTo, int counter)
{
    for (int i = 0; i < counter; ++i)
    {
        addElement(listTo, getHeadName(listFrom), getHeadPhone(listFrom));
        deleteHeadElement(listFrom);
    }
}

int compareHeads(List* firstList, List* secondList, SortKey key)
{
    if (key == name)
    {
        return strcmp(getHeadName(firstList), getHeadName(secondList));
    }
    return strcmp(getHeadPhone(firstList), getHeadPhone(secondList));
}

List* merge(List* firstList, List* secondList, SortKey key)
{
    List* sortedList = createList();
    while (!sizeOfList(firstList) == 0 && !sizeOfList(secondList) == 0)
    {
        compareHeads(firstList, secondList, key) < 0
            ? moveElements(firstList, sortedList, 1)
            : moveElements(secondList, sortedList, 1);
    }
    if (sizeOfList(firstList) == 0)
    {
        moveElements(secondList, sortedList, sizeOfList(secondList));
    }
    else
    {
        moveElements(firstList, sortedList, sizeOfList(firstList));
    }
    deleteList(firstList);
    deleteList(secondList);
    return sortedList;
}

List* mergeSort(List** list, SortKey key)
{
    const int size = sizeOfList(*list);
    if (size <= 1)
    {
        return *list;
    }
    List* firstList = createList();
    moveElements(*list, firstList, size / 2);
    List* secondList = createList();
    moveElements(*list, secondList, size - size / 2);
    deleteList(*list);
    firstList = mergeSort(&firstList, key);
    secondList = mergeSort(&secondList, key);
    List* resultList = merge(firstList, secondList, key);
    return resultList;
}

bool testAddDeleteLength()
{
    List* list = createList();
    if (sizeOfList(list) != 0)
    {
        deleteList(list);
        return false;
    }
    bool isAdded = addElement(list, "test", "111");
    if (!isAdded)
    {
        deleteList(list);
        return false;
    }
    isAdded = addElement(list, "qwerty", "907");
    if (!isAdded || sizeOfList(list) != 2)
    {
        deleteList(list);
        return false;
    }
    deleteHeadElement(list);
    if (strcmp(getHeadName(list), "qwerty") != 0)
    {
        deleteList(list);
        return false;
    }
    deleteList(list);
    return true;
}

bool testSortByName()
{
    List* list = createList();
    bool isAdded = addElement(list, "qwerty", "111");
    isAdded = addElement(list, "werty", "22345") && isAdded;
    isAdded = addElement(list, "abc", "90") && isAdded;
    if (!isAdded)
    {
        deleteList(list);
        return false;
    }
    List* testListOne = mergeSort(&list, name);
    List* correctListOne = createList();
    isAdded = addElement(correctListOne, "abc", "90") && isAdded;
    isAdded = addElement(correctListOne, "qwerty", "111") && isAdded;
    isAdded = addElement(correctListOne, "werty", "22345") && isAdded;
    if (!isAdded)
    {
        deleteList(testListOne);
        deleteList(correctListOne);
        return false;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (strcmp(getHeadPhone(testListOne), getHeadPhone(correctListOne)) != 0)
        {
            deleteList(testListOne);
            deleteList(correctListOne);
            return false;
        }
        deleteHeadElement(testListOne);
        deleteHeadElement(correctListOne);
    }
    deleteList(testListOne);
    deleteList(correctListOne);
    return true;
}

bool testSortByPhone()
{
    List* list2 = createList();
    bool isAdded = addElement(list2, "qwerty", "111");
    isAdded = addElement(list2, "werty", "22345") && isAdded;
    isAdded = addElement(list2, "abc", "90") && isAdded;
    if (!isAdded)
    {
        deleteList(list2);
        return false;
    }
    List* testListTwo = mergeSort(&list2, phone);
    List* correctListTwo = createList();
    isAdded = addElement(correctListTwo, "qwerty", "111") && isAdded;
    isAdded = addElement(correctListTwo, "werty", "22345") && isAdded;
    isAdded = addElement(correctListTwo, "abc", "90") && isAdded;
    if (!isAdded || sizeOfList(correctListTwo) != 3)
    {
        deleteList(testListTwo);
        deleteList(correctListTwo);
        return false;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (strcmp(getHeadPhone(testListTwo), getHeadPhone(correctListTwo)) != 0)
        {
            deleteList(testListTwo);
            deleteList(correctListTwo);
            return false;
        }
        deleteHeadElement(testListTwo);
        deleteHeadElement(correctListTwo);
    }
    deleteList(testListTwo);
    deleteList(correctListTwo);
    return true;
}