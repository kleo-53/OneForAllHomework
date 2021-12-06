#pragma once
#include <stdbool.h>

// This is struct of hash table
typedef struct HashTable HashTable;

// This function creates a hash table
HashTable* createTable(bool* isWorking);

// This function adds value to hash table
void addValueToTable(HashTable* table, char* value, bool* isWorking);

// This function checks if the value is in hash table
bool inTable(HashTable* table, char* value);

// This function returns filling factor of the hash table
float fillingFactor(HashTable* table);

// This function returns maximum length of the list
int maximumLength(HashTable* table);

// This function returns average length of the list
float mediumLength(HashTable* table);

// This function prints hash table
void printTable(HashTable* table);

// This function deletes hash table
void deleteTable(HashTable* table);

// This function checks if hash function works correctly
bool testHash();