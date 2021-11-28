#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#define ARRAY_SIZE 50

int main()
{
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return -1;
    }
    int n = 0;
    fscanf_s(file, "%d", &n);
    int matrix[ARRAY_SIZE][ARRAY_SIZE] = { 0 };
    int inputNumber = 0;
    int i = 0;
    int j = 0;
    while (!feof(file))
    {
        fscanf_s(file, "%d", &inputNumber);
        matrix[i][j] = inputNumber;
        if (j % n == n - 1) 
        {
            j = 0;
            ++i;
        }
        else
        {
            ++j;
        }
    }
    fclose(file);
    for (int k = 1; k < n; ++k)
    {
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }
    FILE* outfile = fopen("output.txt", "w");
    if (file == NULL)
    {
        return -1;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fprintf(outfile, "%d ", matrix[i][j]);
        }
        fprintf(outfile, "\n");
    }
    fclose(outfile);
    return 0;
}
