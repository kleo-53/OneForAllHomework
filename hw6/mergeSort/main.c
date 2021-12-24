#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"
#include "mergeSort.h"

#define ARRAY_SIZE 40

int main()
{
    if (!testAddDeleteLength() || !testSortByName() || !testSortByPhone())
    {
        printf("Tests failed:(");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return -1;
    }
    List* list = createList();
    while (!feof(file))
    {
        char name[ARRAY_SIZE] = "";
        char phone[ARRAY_SIZE] = "";
        fscanf_s(file, "%[^:]%*c%*c", name, 40);
        fscanf_s(file, "%[^\n]%*c", phone, 40);
        bool isAdded = addElement(list, name, phone);
        if (!isAdded)
        {
            printf("some errors have occured.");
            return -1;
        }
    }
    fclose(file);
    printf("Choose:\n1 - sort list by name\n2 - sort list by phone\n");
    int command = 0;
    scanf_s("%d", &command);
    if (command != 1 && command != 2)
    {
        printf("Incorrect command.");
        deleteList(list);
        return -1;
    }
    List* mergeSortList = mergeSort(&list, (command == 2) ? phone : name);
    printf("This is sorted list:\n");
    printList(mergeSortList);
    deleteList(mergeSortList);
    return 0;
}