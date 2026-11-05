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

#define MAX_BUF 1024

static vector* v  = NULL;


void handleSamfetch();

void start_terminal(int args, char **argv) {
    hash_table* ht = loadPath();

    if (ht == NULL) {
        printf("Error");
    }

    // printf("\nvalue: %s", getValue(ht, "ls"));
    // printf("\nvalue: %s", getValue(ht, "pwd"));
    // printf("\nvalue: %s", getValue(ht, "clear"));


    int number_of_args = args;
    char buff[MAX_BUF];

    v = newVector();
    signal(SIGINT, handleExit);

    while (1) {
        //reset length of vector so we can allocate properly again
        v->length = 0;
        
        // clear any residual data causing bugs
        vectorClear(v);

        printf("\nSami-shell> ");
        fflush(stdout);

        // take in charachters from stdin into buffer
        fgets(buff, MAX_BUF, stdin);
    
        // create substring 
        createSubstring(v, buff, getStringLength(buff), ' ');

        // check for parent process needed commands, (cd etc..)
        handleCommandsParent(v->data[0], v->data, ht);

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
        if (command != COMMAND_CD) {
            perror("Error: command not found");
        }
       
    }

    //get string 
    // switch (command) {
    //     case (COMMAND_LS):
    //         handleCommand(v->data[0], v->data);
    //         break;
    //     case (COMMAND_PWD):
    //         handleCommand(v->data[0], v->data);
    //         break;
    //     case (COMMAND_CLEAR):
    //         handleCommand(v->data[0], v->data);
    //         break;
    //     case (COMMAND_SAMFETCH):
    //         handleSamfetch();
    //         break;
    //     case (COMMAND_UNKNOWN):
    //         printf("Unknown Command\n");
    //         break;
    //     case (COMMAND_BINARY):
    //         // handleCommand(v->data[0], v->data);
    //         handleCommand(v->data[0], v->data);
    //     default:
    //         break;
      
    // }
}

// loading path 
hash_table* loadPath() {
    // buffer for loading in file
    char* buffer = malloc(sizeof(char) * 100);

    FILE* fptr;

    fptr = fopen("path.txt", "r");
    if (fptr == NULL) {
        printf("file not openend");
        return NULL;
    }

    // create hash table
    hash_table* ht = newHt();

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
            char* keyH = malloc(strlen(key) +1);
            char* valueH = malloc(strlen(key) +1);

            // printf("\nSleutel: %s -> Pad: %s\n", key, value);

            strcpy(keyH, key);
            strcpy(valueH, value);
            
            // store in ht
            put(ht, keyH, valueH);
        }
    }
   
    // release buffer memory
    free(buffer);
    return ht;
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

    // set pointer to null again on stack
    destroyVector(&v);

    _exit(sig);
}
