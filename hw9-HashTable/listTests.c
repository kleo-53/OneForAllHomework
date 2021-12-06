#include "listTests.h"
#include "list.h"
#include <string.h>

bool addDeleteTest()
{
	List* list = createList();
	char* string = "qwerty";
	bool isWorking = true;
	bool isAdded = addWord(list, string, 2, &isWorking);
	deleteList(list);
	return isWorking && isAdded;
}

bool headFunctionsTest()
{
	List* list = createList();
	char* string = "qwerty";
	bool isWorking = true;
	bool isAdded = addWord(list, string, 2, &isWorking);
	if (!isWorking || !isAdded)
	{
		deleteList(list);
		return false;
	}
	isAdded = addWord(list, string, 1, &isWorking);
	if (listLength(list) != 1 || quantityFromHead(list) != 3 || isAdded || strcmp(returnFromHead(list), string) != 0)
	{
		deleteList(list);
		return false;
	}
	isAdded = addWord(list, "abra", 2, &isWorking);
	deleteFromHead(list);
	if (!isAdded || !isWorking || strcmp(returnFromHead(list), "abra") != 0)
	{
		deleteList(list);
		return false;
	}
	deleteList(list);
	return isWorking && isAdded;
}