#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main()
{
    printf("Enter the number of warriors: ");
    int countOfWariors = 0;
    scanf_s("%d", &countOfWariors);
    printf("Enter the frequency of killing warriors: ");
    int frequency = 0;
    scanf_s("%d", &frequency);

    List* warriorsList = createList();
    for (int i = 1; i < countOfWariors + 1; ++i)
    {
        addElement(i, warriorsList);
    }
    while (countOfWariors != 1)
    {
        for (int i = 0; i < frequency - 1; ++i)
        {
            passElement(warriorsList);
        }
        deleteElement(warriorsList);
        --countOfWariors;
    }
    int result = printRemaining(warriorsList);
    if (result == -1)
    {
        printf("Some errors were occurred.");
        return -1;
    }
    printf("The warrior numbered %d will survive!", result);
    return 0;
}