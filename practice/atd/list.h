#pragma once
#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

List* createList();

void deleteList(List *list);

void deletePosition(Position* position); 

void add(List* list, Position* position, int value);

Position* first(List* list);

Position* next(Position* position);

bool last(Position* position);

int get(List* list, Position* position);

