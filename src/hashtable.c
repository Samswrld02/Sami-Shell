#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

//hash function
int hash(char* string) {
    int hash = 0;

    // loop through character till we hit null terminator
    while (*string){
        hash += *string;
        string++;
    }

    return hash % TABLE_SIZE;
}


hash_table* newHt() {
    
    // allocae table on the heap
    hash_table* p = malloc(sizeof(hash_table));

    if (p == NULL) return NULL;

    // allocate buckets 
    p->buckets = malloc(sizeof(bucket*) * TABLE_SIZE);

    if (p->buckets == NULL) {
        free(p);
        return NULL;
    }

    // set all buckets pointers to null
    for (int i = 0; i < TABLE_SIZE; i++) {
        p->buckets[i] = NULL;
    }

    return  p;
}

void put(hash_table* ht,  char* key, char* value) {

    int index = hash(key);
    // printf("index: %i", index);

    if (ht->buckets[index] == NULL) {
        // printf("bucket is free");
        bucket* node = malloc(sizeof(bucket));
        node->next = NULL;
        ht->buckets[index] = node;
        ht->buckets[index]->key = key;
        ht->buckets[index]->value = value;

        // printf("value of %s is %s",  ht->buckets[index]->key,  ht->buckets[index]->value);
    } else {
        // check if linked list space exists and create new bucket/node
        bucket* node = ht->buckets[index];

        // go deeper if bucket is occupied until you find one pointer that points to null
        while (node != NULL) {
            // check if nodes already have key
            if (strcmp(node->key, key) == 0) {
                printf("key already exists");
                return;
            }

            // check if this is the last one in the row
            if (node->next == NULL) {
                break;
            }
        
            // set new node for next check
            node = node->next;
        }
        
        // create new node/bucket
        bucket* newNode = malloc(sizeof(bucket));
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;

         //link node to new node
        node->next = newNode;
    }
}

char* getValue(hash_table* ht, char* key) {
    // get index
    int index = hash(key);
    // printf("index: %i", index);
    bucket* node = ht->buckets[index];

    // check nodes if nodes not null check value else move to next link
    while (node != NULL) {
        // traverse linked list till you find match, if no match has been found return null
        if (strcmp(node->key, key) == 0) {
            return node->value;
        } 
        node = node->next;
    }

    // if no linked list match either key not found
    return NULL;
} 

