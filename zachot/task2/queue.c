#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct QueueElement
{
    int value;
    int priority;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue
{
    QueueElement* head;
} Queue;

Queue* createQueue()
{
    return (Queue*)calloc(1, sizeof(Queue));
}

void deleteQueue(Queue* queue)
{
    QueueElement* position = queue->head;
    while (position != NULL)
    {
        queue->head = queue->head->next;
        free(position);
        position = queue->head;
    }
    free(queue);
}

bool isEmpty(Queue* queue)
{
    return queue->head == NULL;
}

void enqueue(Queue* queue, int value, int priority, bool* isWorking)
{
    if (isEmpty(queue))
    {
        QueueElement* newRoot = calloc(1, sizeof(QueueElement));
        if (newRoot == NULL)
        {
            *isWorking = false;
            return;
        }
        newRoot->priority = priority;
        newRoot->value = value;
        queue->head = newRoot;
    }
    else
    {
        QueueElement* newElement = calloc(1, sizeof(QueueElement));
        if (newElement == NULL)
        {
            *isWorking = false;
            return;
        }
        newElement->priority = priority;
        newElement->value = value;
        if (queue->head->priority < priority)
        {
            QueueElement* temporary = queue->head;
            queue->head = newElement;
            newElement->next = temporary;
            return;
        }
        QueueElement* current = queue->head;
        QueueElement* next = queue->head->next;
        QueueElement* previous = NULL;
        while (next != NULL && current->priority >= priority)
        {
            previous = current;
            current = next;
            next = next->next;
        }
        if (next != NULL)
        {
            if (current->priority >= priority)
            {
                current->next = newElement;
                newElement->next = next;
            }
            else
            {
                previous->next = newElement;
                newElement->next = current;
            }
        }
        else
        {
            if (current->priority >= priority)
            {
                current->next = newElement;
            }
            else
            {
                previous->next = newElement;
                newElement->next = current;
            }
        }
    }
}

int dequeue(Queue* queue)
{
    if (isEmpty(queue))
    {
        return -1;
    }
    const int highestElement = queue->head->value;
    QueueElement* temporary = queue->head->next;
    queue->head = temporary;
    return highestElement;
}

void printQueueInFile(Queue* queue, FILE* file)
{
    QueueElement* current = queue->head;
    while (current != NULL)
    {
        fprintf(file, "%d: %d, ", current->priority, current->value);
        current = current->next;
    }
}