#ifndef VECTOR_H
#define VECTOR_H 
#include "arena.h"

typedef struct {
    char** data;
    int length;
    int capacity;
} vector;

vector* newVector(Arena* arena);

void vectorAppend(vector* v, char* string);
void destroyVector(vector** v);
void vectorClear(vector* v);

#endif
