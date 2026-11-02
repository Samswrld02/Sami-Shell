#ifndef VECTOR_H
#define VECTOR_H 

typedef struct {
    char** data;
    int length;
    int capacity;
} vector;

vector* newVector();

void vectorAppend(vector* v, char* string);

#endif
