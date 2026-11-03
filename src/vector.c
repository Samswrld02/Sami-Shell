#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define CAPACITY 50

// vector constructor
vector* newVector() {
   vector* v = malloc(sizeof(vector)); 

   // create capacity, holds pointers to strings
   v->data = malloc(CAPACITY * sizeof(char*));

   //set starting length
   v->length = 0;

   //set starting capacity
   v->capacity = CAPACITY;

   return v;
}

void vectorClear(vector* v) {
    memset(v->data, 0, (v->capacity * sizeof(char*)));
}

// create a string vector
void vectorAppend(vector* v, char* string) {
    // realloc for bigger capacity
    if (v->length >= v->capacity) {
        v->capacity = v->capacity * 2;
        v->data = realloc(v->data, v->capacity * sizeof(char*));
    }

    // allocate string pointer to current index which is the length  *
    v->data[v->length] = string;
    
    //move length 
    v->length++;
}

// destructor for vector struct
void destroyVector(vector** v) {
    free((*v)->data);
    free(*v);

    // set pointer to null to prevent memoryleaks
    *v = NULL;
}





