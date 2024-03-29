﻿#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 30

typedef struct Node
{
    int number;
    int country;
} Node;

typedef struct Graph
{
    Node* nodes;
    int nodeCounter;
    int countryCounter;
    int notInCountry;
    int** matrix;
} Graph;

Graph* createGraph(const int nodeCounter, bool* isWorking)
{
    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        *isWorking = false;
        return NULL;
    }
    graph->nodeCounter = nodeCounter;
    graph->notInCountry = nodeCounter;
    graph->nodes = calloc(nodeCounter, sizeof(Node));
    if (graph->nodes == NULL)
    {
        free(graph);
        *isWorking = false;
        return NULL;
    }
    for (int i = 0; i < nodeCounter; ++i)
    {
        graph->nodes[i].country = -1;
        graph->nodes[i].number = i;
    }
    graph->matrix = (int**)malloc(graph->nodeCounter * sizeof(int*));
    if (graph->matrix == NULL)
    {
        free(graph);
        *isWorking = false;
        return NULL;
    }
    for (int i = 0; i < nodeCounter; ++i)
    {
        graph->matrix[i] = (int*)malloc(graph->nodeCounter * sizeof(int));
        if (graph->matrix[i] == NULL)
        {
            free(graph->matrix);
            free(graph);
            *isWorking = false;
            return NULL;
        }
        for (int j = 0; j < nodeCounter; ++j)
        {
            graph->matrix[i][j] = -1;
        }
    }
    return graph;
}

void setMatrix(Graph* graph, const int** nodeMatrix, const int nodeCounter)
{
    for (int i = 0; i < nodeCounter; ++i)
    {
        graph->matrix[nodeMatrix[i][0]][nodeMatrix[i][1]] = nodeMatrix[i][2];
        graph->matrix[nodeMatrix[i][1]][nodeMatrix[i][0]] = nodeMatrix[i][2];
    }
}

void setCountries(Graph* graph, const int* countries, const int countryCounter)
{
    graph->countryCounter = countryCounter;
    for (int i = 0; i < countryCounter; ++i)
    {
        graph->nodes[countries[i]].country = i;
    }
    graph->notInCountry = graph->nodeCounter - countryCounter;
}


void nodesToCountries(Graph* graph)
{
    while (graph->notInCountry > 0)
    {
        for (int country = 0; country < graph->countryCounter; ++country)
        {
            int nearNode = -1;
            int distance = INT_MAX;
            for (int i = 0; i < graph->nodeCounter; ++i)
            {
                if (graph->nodes[i].country == country)
                {
                    for (int j = 0; j < graph->nodeCounter; ++j)
                    {
                        if (graph->matrix[i][j] != -1 && graph->nodes[j].country == -1 && graph->matrix[i][j] < distance)
                        {
                            distance = graph->matrix[i][j];
                            nearNode = j;
                        }
                    }
                }
            }
            if (nearNode != -1)
            {
                graph->nodes[nearNode].country = country;
                --graph->notInCountry;
            }
        }
    }
}

void deleteGraph(Graph* graph)
{
    for (int i = 0; i < graph->nodeCounter; ++i)
    {
        free(graph->matrix[i]);
    }
    free(graph->nodes);
    free(graph);
}

void printNodesByCountries(Graph* graph, bool* isWorking, const bool inFile)
{
    int** countries = (int**)malloc((int)sizeof(int) * graph->countryCounter);
    if (countries == NULL)
    {
        *isWorking = false;
        return;
    }
    for (int i = 0; i < graph->countryCounter; ++i)
    {
        countries[i] = (int*)malloc(sizeof(int*) * graph->nodeCounter);
        if (countries[i] == NULL)
        {
            *isWorking = false;
            return;
        }
        for (int j = 0; j < graph->nodeCounter; ++j)
        {
            countries[i][j] = -1;
        }
    }
    for (int i = 0; i < graph->nodeCounter; ++i)
    {
        int index = 0;
        if (graph->nodes[i].country == -1)
        {
            continue;
        }
        while (countries[graph->nodes[i].country][index] != -1)
        {
            ++index;
        }
        countries[graph->nodes[i].country][index] = graph->nodes[i].number;
    }
    if (!inFile)
    {
        for (int i = 0; i < graph->countryCounter; ++i)
        {
            printf("%d: ", i);
            for (int j = 0; j < graph->nodeCounter; ++j)
            {
                if (countries[i][j] == -1)
                {
                    break;
                }
                printf("%d ", countries[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        FILE* file = fopen("output.txt", "w");
        if (file == NULL)
        {
            *isWorking = false;
            return;
        }
        for (int i = 0; i < graph->countryCounter; ++i)
        {
            fprintf(file, "%d: ", i);
            for (int j = 0; j < graph->nodeCounter; ++j)
            {
                if (countries[i][j] == -1)
                {
                    break;
                }
                fprintf(file, "%d ", countries[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
    for (int i = 0; i < graph->countryCounter; ++i)
    {
        free(countries[i]);
    }
}