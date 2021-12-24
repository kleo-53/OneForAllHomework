#pragma once

#include <stdbool.h>

// Struct of graph
typedef struct Graph Graph;

// This function creates graph with empty adjacency matrix
Graph* createGraph(const int nodeCounter, bool* isWorking);

// This function sets matrix to graph
void setMatrix(Graph* graph, const int** nodeMatrix, const int nodeCounter);

// This function sets countries to given nodes
void setCountries(Graph* graph, const int* countries, const int countryCounter);

// This function distributes other nodes to countries
void nodesToCountries(Graph* graph);

// This function deletes the graph
void deleteGraph(Graph* graph);

// This function prints all nodes grouped by their countries
void printNodesByCountries(Graph* graph, bool* isWorking, const bool inFile);