#include "terminal.h"
#include "customString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "vector.h"
#include "commands.h"
#include <sys/wait.h>
#include <stdbool.h>
#include "hashtable.h"
#include "arena.h"

#define MAX_BUF 1024

static vector* v = NULL;
static Arena* arena = NULL;

void handleSamfetch();

void start_terminal() {

    arena = initArena(1024);
    if (arena == NULL) {
        printf("arena memory allocation failed !");
        exit(EXIT_FAILURE);
    }

    hash_table* ht = newHt(arena);
    loadPath(arena, ht);

    char buff[MAX_BUF];

    v = newVector(arena);

    signal(SIGINT, handleExit);

    while (1) {
        //reset length of vector so we can allocate properly again
        v->length = 0;
        
        // clear any residual data causing bugs
        vectorClear(v);

        printf("\nSami-shell> ");
        fflush(stdout);

        // take in characters from stdin into buffer
        fgets(buff, MAX_BUF, stdin);
    
        // create substring 
        createSubstring(v, buff, getStringLength(buff), ' ');

        // check for parent process needed commands, (cd etc..)
        int ok = handleCommandsParent(arena, v->data[0], v->data);

        // skip forking if command is parent only
        if (ok) {
            continue;
        }
       
        // fork start child process
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("process couldnt be spawned");
        }
        else if (pid == 0) {
            handleProcess(v, ht);
            break;
        }
        else{
            waitpid(pid, NULL, 0);
            // reset arena for next command/ request
            resetArena(arena);
        }
    }
}

// turn string into command
CommandType stringToCommand(char* str) {
    if (strcmp(str, "ls") == 0) return COMMAND_LS;
    if (strcmp(str, "pwd") == 0) return COMMAND_PWD;
    if (strcmp(str, "clear") == 0) return COMMAND_CLEAR;
    if (strcmp(str, "samfetch") == 0) return COMMAND_SAMFETCH;
    if (strcmp(str, "exit") == 0 ) return COMMAND_EXIT;
    if (strcmp(str, "cd") == 0 ) return COMMAND_CD;
    if (checkBinary(str) == 1) return COMMAND_BINARY;

    return COMMAND_UNKNOWN;
}

void handleCommand(char* str, char** args) {
    fflush(stdout);
    if (execvp(str, args) == -1) perror("error");
}

// takes in the argument list
void handleProcess(vector* v, hash_table* ht) {
    // get the command enum
    CommandType command = stringToCommand(v->data[0]);

    char* commandV;

    if (commandV = getValue(ht, v->data[0])) {
        if (execvp(commandV, v->data) == -1) perror("error");
    } else {
        if (command == COMMAND_BINARY) {
            execvp(v->data[0], v->data);
        }
        if (command == COMMAND_SAMFETCH) {
            handleSamfetch();
        } else {
            perror("Error: command not found");
        }
       
    }
}

// loading path 
void loadPath( Arena* arena, hash_table* ht) {
    // buffer for loading in file
    char* buffer = allocateData(arena, sizeof(char) * 100);

    FILE* fptr;

    fptr = fopen("path.txt", "r");
    if (fptr == NULL) {
        printf("file not openend");
        exit(EXIT_FAILURE);
    }


    char* path;
    // load in path from file and tokenise
    while ((path = fgets(buffer, (sizeof(char) * 100), fptr)) != NULL) {
         // Capture key
        char* key = strtok(path, "=");
        
        // capture value
        char* value = strtok(NULL, "\r\n"); 

        // if both available
        if (key != NULL && value != NULL) {

            // allocate data on the heap for the strings
            char* keyH = allocateData(arena, strlen(key) + 1);
            char* valueH = allocateData(arena, strlen(value) + 1);

            // printf("\nSleutel: %s -> Pad: %s\n", key, value);

            strcpy(keyH, key);
            strcpy(valueH, value);
            
            // store in ht
            put(arena, ht, keyH, valueH);
        }
    }
}

void handleSamfetch() {
     printf("                      \n"
           "  ___________    ____  \n"
           " /  ___/\\__  \\  /    \\ \n"
           " \\___ \\  / __ \\|   |  \\\n"
           "/____  >(____  /___|  /\n"
           "     \\/      \\/     \\/\n");
}


void handleExit(int sig) {
    char msg[] = "\ngoodbye from sami :)\n";
    write(STDOUT_FILENO, msg, sizeof(msg));

    // free arena allocated memory
    freeArena(arena);
   
    _exit(sig);
}
