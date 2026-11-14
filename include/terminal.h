#ifndef TERMINAL_H
#define TERMINAL_H 
#include <stdbool.h>
#include "hashtable.h"
#include "vector.h"

void start_terminal();
void loadPath(Arena* arena, hash_table* ht);

void handleProcess(vector* v, hash_table* ht);

void handleExit(int sig);

typedef struct {
    char* args;
    int length;
} arguments;


#endif