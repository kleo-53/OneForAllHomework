#pragma once

#include <stdbool.h>

// This function checks if qsort sorts the array correctly
bool qsortCheck(int* sortingArray, int* correctArray, int arraySize);

// This function checks if programm finds frequent element correctly
void frequentElementCheck(int* inputArray, int arraySize, int* maximumCounter, int* frequentElement);

// This function checks if test executed without errors
bool testCorrectCase();