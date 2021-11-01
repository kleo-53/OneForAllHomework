#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "List.h"

#define ARRAY_SIZE 40

void moveElements(List* listFrom, List* listTo, int counter)
{
				for (int i = 0; i < counter; ++i)
				{
								addElement(listTo, getHeadName(listFrom), getHeadPhone(listFrom));
								deleteHeadElement(listFrom);
				}
}

List* mergeSort(List* firstList, List* secondList, int command)
{
				List* sortedList = createList();
				while (!sizeOfList(firstList) == 0 && !sizeOfList(secondList) == 0)
				{
								if (command == 1)
								{
												if (strcmp(getHeadName(firstList), getHeadName(secondList)) < 0)
												{
																moveElements(firstList, sortedList, 1);
												}
												else
												{
																moveElements(secondList, sortedList, 1);
												}
								}
								else
								{
												if (strcmp(getHeadPhone(firstList), getHeadPhone(secondList)) < 0)
												{
																moveElements(firstList, sortedList, 1);
												}
												else
												{
																moveElements(secondList, sortedList, 1);
												}
								}
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

List* mainMergeSort(List** list, int command)
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
				firstList = mainMergeSort(&firstList, command);
				secondList = mainMergeSort(&secondList, command);
				List* resultList = mergeSort(firstList, secondList, command);
				return resultList;
}

int main()
{
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
								addElement(list, name, phone);
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
				List* mergeSortList = mainMergeSort(&list, command);
				printf("This is sorted list:\n");
				printList(mergeSortList);
}