#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 100

bool isPalindrome(char* string, int stringSize)
{
    const int middle = stringSize / 2;
    for (int i = 0; i <= middle; ++i)
    {
        if (string[i] != string[stringSize - i - 1])
        {
            return false;
        }
    }
    return true;
}

void deleteSpaces(char* string)
{
    char* i = string;
    char* j = string;
    while (*j != 0)
    {
        *i = *j++;
        if (*i != ' ')
        {
            ++i;
        }
    }
    *i = 0;
}
bool checkTest(char *string, char* correctString, int correctSize, int correctDeleteSize)
{
    int sizeString = strlen(string);
    if (sizeString != correctSize)
    {
        return false;
    }
    deleteSpaces(string);
    sizeString = strlen(string);
    if (sizeString != correctDeleteSize)
    {
        return false;
    }
    for (int i = 0; i < sizeString; ++i)
    {
        if (string[i] != correctString[i])
        {
            return false;
        }
    }
}
bool testCorrectCase()
{
    char string[ARRAY_SIZE] = "q q wq    q";
    char correct[ARRAY_SIZE] = "qqwqq";
    int correctSize = strlen(string);
    int correctDeleteSize = strlen(correct);
    if (!checkTest(string, correct, correctSize, correctDeleteSize) || !isPalindrome(string, correctDeleteSize)) 
    {
        return false;
    }
    return true;
}

bool testIncorrectCase()
{
    char string[ARRAY_SIZE] = "q z wq z   q";
    char correct[ARRAY_SIZE] = "qzwqzq";
    int correctSize = strlen(string);
    int correctDeleteSize = strlen(correct);
    if (!checkTest(string, correct, correctSize, correctDeleteSize) || isPalindrome(string, correctDeleteSize)) 
    {
        return false;
    }
    return true;
}

int main()
{
    if (!testCorrectCase() || !testIncorrectCase())
    {
        printf("Tests failed.");
        return 1;
    }
    char inputString[ARRAY_SIZE] = { '0' };
    scanf_s("%[^\n]%*c", &inputString, ARRAY_SIZE);
    deleteSpaces(inputString);
    const int sizeString = strlen(inputString);
    printf("%s", isPalindrome(inputString, sizeString) ? "This string is palindrome:)" : "This string is not palindrome:(");
}