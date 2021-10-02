#include <stdio.h>
#include <string.h>

const char* checkBalance(char str[])
{
    int counter = 0;

    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] == '(')
        {
            ++counter;
        }
        else if (str[i] == ')')
        {
            if (counter <= 0)
            {
                return "String is not balanced.";
            }
            --counter;
        }
    }
    if (counter != 0)
    {
        return "String is not balanced.";
    }
    return "String is balanced.";
}

int main()
{
    int counter = 0;
    char str[40];

    printf("Enter a string consisting of brackets: ");
    scanf("%s", &str);
    printf("%s\n", checkBalance(str));
}
