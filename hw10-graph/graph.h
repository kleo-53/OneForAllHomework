#pragma once

#include <stdbool.h>

typedef struct Graph Graph;

Graph* createGraph(const int nodeCounter, bool* isWorking);

void setMatrix(Graph* graph, const int** nodeMatrix, const int nodeCounter);

void setCountries(Graph* graph, const int* countries, const int countryCounter);

void nodesToCountries(Graph* graph);

void deleteGraph(Graph* graph);

void printNodesByCountries(Graph* graph, bool* isWorking, const bool inFile);