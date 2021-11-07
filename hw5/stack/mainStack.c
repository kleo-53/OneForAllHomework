#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "stackTests.h"

int main()
{
    if (!testIsEmpty() || !testPopEmptyStack() || !testStackWorks())
    {
        printf("Tests failed.");
        return -1;
    }
    return 0;
}