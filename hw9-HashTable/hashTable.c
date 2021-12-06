#define _CRT_SECURE_NO_WARNINGS

#include "hashTable.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct HashTable
{
    int size;
    int quantity;
    float fillingFactor;
    List** elements;
} HashTable;

HashTable* createTable(bool* isWorking)
{
    HashTable* table = calloc(1, sizeof(List*));
    if (table == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    table->size = 31;
    table->elements = calloc(table->size, sizeof(List*));
    if (table->elements == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    for (int i = 0; i < table->size; ++i)
    {
        table->elements[i] = createList();
    }
    return table;
}

int hashFunction(char* string, int tableSize)
{
    const int size = (int)strlen(string);
    int hash = 0;
    for (int i = 0; i < size; ++i)
    {
        hash = (hash + string[i]) % tableSize;
    }
    return hash;
}

void rehashing(HashTable* table, bool* isWorking)
{
    List* temporary = createList(table->size);
    for (int i = 0; i < table->size; ++i)
    {
        while (!isEmpty(table->elements[i]))
        {
            char* value = returnFromHead(table->elements[i]);
            addWord(temporary, value, quantityFromHead(table->elements[i]), isWorking);
            deleteFromHead(table->elements[i]);
        }
        deleteList(table->elements[i]);
    }
    free(table->elements);
    table->size *= 2;
    table->quantity = 0;
    table->elements = calloc(table->size, sizeof(List*));
    for (int i = 0; i < table->size; ++i)
    {
        table->elements[i] = createList(table->size);
    }
    while (!isEmpty(temporary))
    {
        char* value = returnFromHead(temporary);
        int hash = hashFunction(value, table->size);
        const bool newElementAdded = addWord(table->elements[hash], value, quantityFromHead(temporary), isWorking);
        if (!(*isWorking))
        {
            return;
        }
        if (newElementAdded)
        {
            ++table->quantity;
            table->fillingFactor = (float)table->quantity / table->size;
        }
        deleteFromHead(temporary);
    }
    deleteList(temporary);
}

void addValueToTable(HashTable* table, char* value, bool* isWorking)
{
    int currentHash = hashFunction(value, table->size);
    bool isAdded = addWord(table->elements[currentHash], value, 1, isWorking);
    if (isAdded)
    {
        ++table->quantity;
        table->fillingFactor = (float)table->quantity / table->size;
    }
    if (table->fillingFactor > 1.0)
    {
        rehashing(table, isWorking);
    }
}

bool inTable(HashTable* table, char* value)
{
    return inList(table->elements[hashFunction(value, table->size)], value);
}

float fillingFactor(HashTable* table)
{
    return table->fillingFactor;
}

int maximumLength(HashTable* table)
{
    int maximum = 0;
    for (int i = 0; i < table->size; ++i)
    {
        const int current = listLength(table->elements[i]);
        if (current > maximum)
        {
            maximum = current;
        }
    }
    return maximum;
}

float mediumLength(HashTable* table)
{
    int summaryOfAll = 0;
    int numberOfAll = 0;
    for (int i = 0; i < table->size; ++i)
    {
        if (!isEmpty(table->elements[i]))
        {
            summaryOfAll += listLength(table->elements[i]);
            ++numberOfAll;
        }
    }
    return numberOfAll == 0 ? 0 : (float)summaryOfAll / numberOfAll;
}

void printTable(HashTable* table)
{
    for (int i = 0; i < table->size; ++i)
    {
        printList(table->elements[i]);
    }
}

void deleteTable(HashTable* table)
{
    for (int i = 0; i < table->size; ++i)
    {
        deleteList(table->elements[i]);
    }
    deleteList(*(table->elements));
    free(table);
}

bool testHash()
{
    char string1[] = "abracadabra";
    char string2[] = "karkarkarka";
    return hashFunction(string1, 15) != hashFunction(string2, 15);
}