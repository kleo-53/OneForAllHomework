#include <stdio.h>

#define strSize 40

int main()
{
    int a = 0;
    int b = 0;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int sign = 1;
    int quotient = 0;
    int checknegative = 0;

    if (a < 0 && b > 0)
    {
        a = -a;
        sign = -1;
        checknegative = -1;
    }
    else if (a >= 0 && b < 0)
    {
        b = -b;
        sign = -1;
    }
    else if (a <= 0 && b < 0)
    {
        a = -a;
        b = -b;
        checknegative = 1;
    }

    if (b == 0)
    {
        printf("Cannot be divided by 0. Please enter correct data.");
    }
    else
    {
        int summand = b;

        while (summand <= a)
        {
            summand += b;
            quotient += 1;
        }

        printf("The quotient of dividing a by b: %d\n", quotient * sign + checknegative);
    }
}