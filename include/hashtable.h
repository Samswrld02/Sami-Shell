#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_NAME  256
#define TABLE_SIZE 10

#include <stdbool.h>

typedef struct bucket{
    char* key;
    char* value;
    struct bucket* next;
} bucket;

// hash table struct contains buckets
typedef struct hash_table{
    bucket** buckets;
    int capacity;
} hash_table;

typedef struct response {
    hash_table* ht;
    bool ok;
} response;

//hash function
int hash(char* string);

int hash(char* string);
hash_table* newHt();
void put(hash_table* ht,  char* key, char* value);
char* getValue(hash_table* ht, char* key);





#endif