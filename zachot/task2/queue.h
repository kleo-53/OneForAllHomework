#pragma once
#include <stdio.h>
#include <stdbool.h>

// This is struct of queue
typedef struct Queue Queue;

// This function creates new queue
Queue* createQueue();

// This function deletes queue
void deleteQueue(Queue* queue);

// This function checks if queue is empty
bool isEmpty(Queue* queue);

// This function gives the value with highest priority and deletes it from queue
int dequeue(Queue* queue);

// This function finds suitable position to value by its priority and adds them to queue
void enqueue(Queue* queue, int value, int priority, bool* isWorking);

// This function prints queue in given file
void printQueueInFile(Queue* queue, FILE* file);