#include <stdio.h>

int main()
{
    int first = 0;
    int second = 0;

    printf("Enter two integers separated by a space:");
    scanf("%d %d", &first, &second);

    first = first ^ second;
    second = second ^ first;
    first = first ^ second;

    printf("The program swapped numbers without using additional variables: %d %d\n", first, second);
}
