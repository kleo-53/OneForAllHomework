#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 100
#define RANGE 11

const char* deleteRepeating(char* givenString)
{
    int stringSize = strlen(givenString);
    char* resultString = givenString[0];
    char currentElement = givenString[0];

    for (int i = 1; i < stringSize; ++i) 
    {
        if (givenString[i] != currentElement)
        {
            currentElement = givenString[i];
            strcat(resultString, currentElement);
        }
    }
    if (givenString[stringSize - 1] != currentElement)
    {
        strcat(resultString, givenString[stringSize - 1]);
    }

    return resultString;
}

bool createArrayCheck(int* createArray)
{
    if (createArray == NULL)
    {
        printf("Calloc function broke :(");
        return false;
    }
    return true;
}

int main()
{
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("The file is empty!");
        return 1;
    }
    int linesRead = 0;
    printf("\nThere are records in file without repeated elements:");

    while (!feof(file)) {
        char* buffer = malloc(sizeof(char) * 100);
        if (!createArrayCheck(buffer))
        {
            return -1;
        }
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }
        const char* resultString = deleteRepeating(buffer);
        printf("\n%s", resultString);
        ++linesRead;
    }
    fclose(file);
}
