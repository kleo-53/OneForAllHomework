#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashTable.h"
#include "list.h"
#include "listTests.h"

#define ARRAY_SIZE 50

bool testHashTable()
{
	FILE* file = fopen("test.txt", "r");
	if (!file)
	{
		return false;
	}
	bool isWorking = true;
	HashTable* table = createTable(&isWorking);
	if (!isWorking)
	{
		return false;
	}
	while (!feof(file))
	{
		char buffer[ARRAY_SIZE] = "";
		fscanf_s(file, "%[^ \n]%*c", buffer, ARRAY_SIZE);
		if (strlen(buffer) > 0)
		{
			addValueToTable(table, buffer, &isWorking);
			if (!isWorking)
			{
				deleteTable(table);
				return false;
			}
		}
		else
		{
			fscanf_s(file, "%*c");
		}
	}
	fclose(file);
	return 0.983871 - fillingFactor(table) < 0.000001 && maximumLength(table) == 5 && 1.694444 - mediumLength(table) < 0.000001;
}

int main()
{
	if (!testHash() || !addDeleteTest() || !headFunctionsTest() || !testHashTable())
	{
		printf("Tests were failed.");
		return -1;
	}
	FILE* file = fopen("input.txt", "r");
	if (!file)
	{
		return -1;
	}
	bool isWorking = true;
	HashTable* table = createTable(&isWorking);
	if (!isWorking)
	{
		printf("Some errors were occured.");
		return -1;
	}
	while (!feof(file))
	{
		char buffer[ARRAY_SIZE] = "";
		fscanf_s(file, "%[^ \n]%*c", buffer, ARRAY_SIZE);
		if (strlen(buffer) > 0)
		{
			addValueToTable(table, buffer, &isWorking);
		}
		else
		{
			fscanf_s(file, "%*c");
		}
		if (!isWorking)
		{
			printf("Some errors were occured.");
			return -1;
		}
	}
	fclose(file);
	printf("Words in table:\n");
	printTable(table);
	printf("\n\nFilling factor: %f", fillingFactor(table));
	printf("\nMaximum length of the list: %d", maximumLength(table));
	printf("\nAverage list length: %f\n", mediumLength(table));
}