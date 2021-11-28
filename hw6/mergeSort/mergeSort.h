#pragma once
#include "List.h"

// This function sorts list by merge sort 
List* mainMergeSort(List** list, int key);

// This function tests if add and delete functions work correctly
bool testAddDeleteLength();

// This function tests if merge sort by name works correctly
bool testSortByName();

// This function tests if merge sort by name works correctly
bool testSortByPhone();