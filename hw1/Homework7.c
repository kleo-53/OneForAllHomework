#include <stdio.h>

#define arraySize 40

void reverse(int* massiv, int left, int right)
{
    int tmp = 0;
    int boarder = left + (right - left) / 2;

    for (int i = left; i <= boarder; ++i)
    {
        tmp = massiv[right - i + left];
        massiv[right - i + left] = massiv[i];
        massiv[i] = tmp;
    }
}


int main()
{
    int n = 0;
    int m = 0;
    int massiv[arraySize] = { 0 };

    printf("Enter m and n: ");
    scanf("%d %d", &m, &n);
    printf("Enter array elements: ");

    for (int i = 1; i <= n + m; ++i)
    {
        scanf("%d", &massiv[i]);
    }

    reverse(massiv, 1, m);
    reverse(massiv, m + 1, m + n);
    reverse(massiv, 1, m + n);

    printf("The programm had reversed parts of array: ");

    for (int i = 1; i <= m + n; ++i) 
    {
        printf("%d ", massiv[i]);
    }
}
