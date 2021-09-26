#include <stdio.h>
#include <stdbool.h>

bool isPrime(int number)
{
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int number = 0;

    printf("Enter a number: ");
    scanf("%d", &number);
    printf("This numbers up to the entered are prime:\n");

    for (int i = 2; i <= number; ++i)
    {
        if (isPrime(i)) 
        {
            printf("%d\n", i);
        }
    }

}
