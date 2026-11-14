#ifndef ARENA_H
#define ARENA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// arena struct
typedef struct Arena {
    size_t size;
    size_t capacity;
    u_int8_t *data;
    struct Arena* next;
} Arena;

// create arena
Arena* initArena(size_t capacity);

void resetArena(Arena* arena);

void freeArena(Arena* arena);

void arenaSize(Arena* arena);

void* allocateData(Arena* arena, size_t size);





#endif