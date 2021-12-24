#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

bool testBigAddCase()
{
	Queue* queue = createQueue();
	bool isWorking = true;
	enqueue(queue, 1, 5, &isWorking);
	enqueue(queue, 1024, 1, &isWorking);
	enqueue(queue, 3, 3, &isWorking);
	enqueue(queue, 1, 68, &isWorking);
	enqueue(queue, 42, 3, &isWorking);
	enqueue(queue, 555, 18, &isWorking);
	FILE* output = fopen("test.txt", "w");
	printQueueInFile(queue, output);
	fclose(output);
	FILE* file = fopen("test.txt", "r");
	char correctLine[50] = { "68: 1, 18: 555, 5: 1, 3: 3, 3: 42, 1: 1024, " };
	char fileLine[50] = { " " };
	fgets(fileLine, 50, file);
	fclose(file);
	deleteQueue(queue);
	return isWorking && strcmp(fileLine, correctLine) == 0;
}

bool testEqualCase()
{
	Queue* queue = createQueue();
	bool isWorking = true;
	enqueue(queue, 1, 4, &isWorking);
	enqueue(queue, 1024, 4, &isWorking);
	enqueue(queue, 3, 4, &isWorking);
	enqueue(queue, 1, 4, &isWorking);
	FILE* output = fopen("test.txt", "w");
	printQueueInFile(queue, output);
	fclose(output);
	FILE* file = fopen("test.txt", "r");
	char correctLine[40] = { "4: 1, 4: 1024, 4: 3, 4: 1, " };
	char fileLine[40] = { " " };
	fgets(fileLine, 40, file);
	fclose(file);
	const int highest = dequeue(queue);
	const int next = dequeue(queue);
	deleteQueue(queue);
	return isWorking && strcmp(fileLine, correctLine) == 0 && highest == 1 && next == 1024;
}

bool testDeleteCase()
{
	Queue* queue = createQueue();
	bool isWorking = true;
	enqueue(queue, 1, 5, &isWorking);
	enqueue(queue, 555, 18, &isWorking);
	FILE* output = fopen("test.txt", "w");
	printQueueInFile(queue, output);
	fclose(output);
	FILE* file = fopen("test.txt", "r");
	char correctLine[20] = { "18: 555, 5: 1, " };
	char fileLine[20] = { " " };
	fgets(fileLine, 20, file);
	fclose(file);
	const int first = dequeue(queue);
	const int second = dequeue(queue);
	const int third = dequeue(queue);
	const int fourth = dequeue(queue);
	deleteQueue(queue);
	return isWorking && strcmp(fileLine, correctLine) == 0 && first == 555 && second == 1 && third == -1 && fourth == -1;
}

int main()
{
	if (!testEqualCase() || !testBigAddCase() || !testDeleteCase())
	{
		printf("Tests failed:(");
		return -1;
	}
	printf("Tests passed:)");
	return 0;
}