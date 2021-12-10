#pragma once
#include "List.h"

// The key by which sorting is performed
typedef enum SortKey SortKey;

// This function sorts list by merge sort 
List* mergeSort(List** list, SortKey key);

// This function tests if add and delete functions work correctly
bool testAddDeleteLength();

// This function tests if merge sort by name works correctly
bool testSortByName();

// This function tests if merge sort by name works correctly
bool testSortByPhone();