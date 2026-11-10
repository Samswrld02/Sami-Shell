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
Arena* initArena(size_t capacity) {

    // allocate data
   void* data = malloc(sizeof(uint8_t) * capacity);

   Arena* arena = malloc(sizeof(Arena));

   arena->capacity = capacity;
   arena->size = 0;
   arena->data = data;
   arena->next = NULL;

    return arena;
}

// reset starting address
void resetArena(Arena* arena) {
    arena->size = 0;
}

// free arena
void freeArena(Arena* arena) {
    // loop through all linked lists

    Arena* current = arena;

    while (current != NULL) {
        Arena* next = current->next;
        free(current->data);
        free(current);

        current = next;
    }
}

void arenaSize(Arena* arena) {
    printf("arena size %zu\n arena capacity: %zu\n", arena->size, arena->capacity);
}

void* allocateData(Arena* arena, size_t size) {
    while ((size + arena->size) > arena->capacity) {
        // create new arena if no node linked
        if (arena->next == NULL) {
            // create new node with double the capacity
            Arena* next = initArena(arena->capacity * 2);

            arena->next = next;    
        }

        // set new arena to be evaluated
        arena = arena->next;
    }

    // return pointer to mem block + offset thats been alligned
    void* p = arena->data + arena->size;

    // set offset with allignment of 8 -> add max remainder and remove max remainder bits so bits 1,2,4 -> max remainder -> 7 in binary = 0000 0111 -> 1111 1000 mask
    arena->size = arena->size + ((size + 7) & ~7);

    return p;
}
