﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int menu(List* myList)
{
    printf("\n0 - Finish work");
    printf("\n1 - Add data in sorted list");
    printf("\n2 - Delete data from sorted list");
    printf("\n3 - Print sorted list");
    printf("\nChose the command: ");

    char command = ' ';
    scanf_s("%c", &command, 2);
    switch (command)
    {
    case '0':
        return -1;
    case '1':
    {
        printf("Enter data: ");
        int data = 0;
        scanf_s("%d%*c", &data);
        addData(myList, data);
        printf("The data %d added successfully!\n", data);
        break;
    }
    case '2':
    {
        printf("Enter data: ");
        int data = 0;
        scanf_s("%d%*c", &data);
        if (!deleteData(myList, data))
        {
            printf("This data not in list!\n");
        }
        else
        {
            printf("The data %d deleted successfully!\n", data);
        }
        break;
    }
    case '3':
    {
        scanf_s("%*c");
        if (isEmpty(myList))
        {
            printf("The list is empty!\n");
        }
        else
        {
            printf("There are all data in the list:\n");
            printList(myList);
            printf("\n");
        }
        break;
    }
    default:
        scanf_s("%*c");
        printf("No option selected\n");
    }
    return 0;
}

int main()
{
    List* myList = createList();
    int result = menu(myList);
    while (result != -1)
    {
        result = menu(myList);
    }
    deleteList(myList);
}