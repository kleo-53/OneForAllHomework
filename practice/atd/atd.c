#include <stdio.h>
#include "list.h"

int main()
{
    List* myList = createList();
    add(myList, first(myList), 1);
    add(myList, first(myList), 2);

    for (Position* i = first(myList); !last(i); i = next(i))
    {
        printf("%d ", get(myList, i));
    }
}