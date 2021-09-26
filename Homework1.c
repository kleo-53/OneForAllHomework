#include <stdio.h>

#define arraySize 28

int main()
{

    int counter[arraySize] = { 0 };

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                ++counter[i + j + k];
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < arraySize; ++i)
    {
        answer += counter[i] * counter[i];
    }

    printf("Number of lucky tickets: %d", answer);
}
