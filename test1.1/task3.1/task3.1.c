#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* oneNumberFile = fopen("g.txt", "r");
    if (oneNumberFile == NULL) {
        return -1;
    }
    int controlNumber = 0;
    fscanf_s(oneNumberFile, "%d", &controlNumber);
    fclose(oneNumberFile);

    FILE* numbersFile = fopen("f.txt", "r");
    if (numbersFile == NULL) {
        return -1;
    }
    FILE* output = fopen("h.txt", "w");
    if (output == NULL) {
        return -1;
    }
    int inputNumber = 0;
    while (!feof(numbersFile)) {
        fscanf_s(numbersFile, "%d", &inputNumber);
        if (inputNumber < controlNumber)
        {
            fprintf(output, "%d\n", inputNumber);
        }
    }
    fclose(numbersFile);
    fclose(output);
}