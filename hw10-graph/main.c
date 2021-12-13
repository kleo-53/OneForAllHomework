#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include <string.h>

bool testCase()
{
    bool isWorking = true;
    Graph* graph = createGraph(4, &isWorking);
    if (!isWorking)
    {
        return false;
    }
    const int testRoads[5][3] = { {0, 1, 3}, {0, 2, 18}, {3, 1, 2}, {2, 3, 1}, {1, 2, 4} };
    int** roads = (int**)malloc(20); 
    if (roads = NULL)
    {
        deleteGraph(graph);
        return -1;
    }
    for (int i = 0; i < 5; ++i)
    {
        (int*)roads[i] = (int*)malloc(12); 
        if (roads[i] == NULL)
        {
            deleteGraph(graph);
            return -1;
        }
        roads[i][0] = testRoads[i][0];
        roads[i][1] = testRoads[i][1];
        roads[i][2] = testRoads[i][2];
    }
    setMatrix(graph, roads, 5);
    int countries[2] = { 0, 3 };
    setCountries(graph, countries, 2);
    nodesToCountries(graph);
    printNodesByCountries(graph, &isWorking, true);
    if (!isWorking)
    {
        deleteGraph(graph);
        return false;
    }
    FILE* file = fopen("test2.txt", "r");
    char* correctCountries[2] = {"0: 0 1 ", "1: 2 3 "};
    char* fileString = malloc(20);
    if (fileString == NULL)
    {
        deleteGraph(graph);
        return false;
    }
    for (int i = 0; i < 2; ++i)
    {
        fgets(fileString, 20, file);
        if (strcmp(fileString, correctCountries[0]) != 0)
        {
            deleteGraph(graph);
            return false;
        }
    }
    deleteGraph(graph);
    return true;
}

int main()
{
    if (!testCase())
    {
        printf("Tests failed.");
        return -1;
    }
    FILE* file = fopen("input.txt", "r");
    int cityCounter = 0;
    fscanf_s(file, "%d", &cityCounter);
    int roadsCounter = 0;
    fscanf_s(file, "%d", &roadsCounter);
    bool isWorking = true;
    Graph* graph = createGraph(cityCounter, &isWorking);
    int** roads = (int**)malloc(sizeof(int*) * (roadsCounter));
    if (roads = NULL)
    {
        deleteGraph(graph);
        return -1;
    }
    int firstCity = 0;
    int secondCity = 0;
    int length = 0;
    for (int i = 0; i < roadsCounter; ++i)
    {
        fscanf_s(file, "%d %d %d", &firstCity, &secondCity, &length);
        roads[i] = malloc(sizeof(int) * 3); 
        if (roads[i] = NULL)
        {
            deleteGraph(graph);
            return -1;
        }
        roads[i][0] = firstCity;
        roads[i][1] = secondCity;
        roads[i][2] = length;
    }
    setMatrix(graph, roads, roadsCounter);
    for (int i = 0; i < roadsCounter; ++i)
    {
        free(roads[i]);
    }
    free(roads);
    int countryCounter = 0;
    fscanf_s(file, "%d", &countryCounter);
    int* countries = (int*)malloc(sizeof(int) * (countryCounter));
    int currentCountry = 0;
    for (int i = 0; i < countryCounter; ++i)
    {
        fscanf_s(file, "%d", &currentCountry);
        countries[i] = currentCountry;
    }
    fclose(file);
    setCountries(graph, countries, countryCounter);
    free(countries);
    nodesToCountries(graph);
    printNodesByCountries(graph, &isWorking, false);
    deleteGraph(graph);
    return 0;
}