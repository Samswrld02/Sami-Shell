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
Arena initArena(size_t capacity) {

    // allocate data
   void* data = malloc(sizeof(uint8_t) * capacity);

    Arena arena = {
        .capacity = capacity,
        .size = 0,
        .data = data,
        .next = NULL,
    };

    return arena;
}

void arenaSize(Arena* arena) {
    printf("arena size %zu\n arena capacity: %zu\n", arena->size, arena->capacity);
}

void* allocateData(Arena* arena, size_t size) {
    // check if space, if not return
    if ((size + arena->size) > arena->capacity) {
        perror("exceeded capacity");
        exit(EXIT_FAILURE);
    }


    // return pointer to mem block
    void* p = arena->data + arena->size;

     // change size
    arena->size = arena->size + size;

    return p;
}


int main(void) {

    Arena arena = initArena(16);

    char* test = "hello worssddd";
    
    char* p = allocateData(&arena, strlen(test) + 1);

    memcpy(p, test, strlen(test) + 1);

    arenaSize(&arena);

    printf("string is %s\n", p);

    int smallint = 2000;
    int* p1 = allocateData(&arena, sizeof(int));

    memcpy(p1, &smallint, sizeof(smallint));

    

   

    printf("%s\n", p);

    
    
    arenaSize(&arena);
    arenaSize(&arena);

    return 0;
}
