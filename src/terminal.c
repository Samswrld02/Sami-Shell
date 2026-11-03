#include "terminal.h"
#include "customString.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "vector.h"
#include "commands.h"
#include <sys/wait.h>

#define MAX_BUF 1024

static vector* v  = NULL;

void handleProcess(vector* v);
void handleSamfetch();

void start_terminal(int args, char **argv) {
    int number_of_args = args;
    char buff[MAX_BUF];

    v = newVector();
    signal(SIGINT, handleExit);

    while (1) {
        //reset length of vector so we can allocate properly again
        v->length = 0;
        
        // clear any residual data causing bugs
        vectorClear(v);

        printf("Sami-shell> ");

        // take in charachters from stdin into buffer
        fgets(buff, MAX_BUF, stdin);
    
        // create substring 
        createSubstring(v, buff, getStringLength(buff), ' ');

        // check for parent process needed commands, (cd etc..)
        handleCommandsParent(v->data[0], v->data);

        // fork start child process
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("process couldnt be spawned");
        }
        else if (pid == 0) {
            handleProcess(v);
            break;
        }
        else{
            wait(&pid);
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

    return COMMAND_UNKNOWN;
}

void handleCommand(char* str, char** args) {
    if (execvp(str, args) == -1) perror("error");
}

// takes in the argument list
void handleProcess(vector* v) {
    // get the command enum
    CommandType command = stringToCommand(v->data[0]);

    //get string 
    switch (command) {
        case (COMMAND_LS):
            handleCommand(v->data[0], v->data);
            break;
        case (COMMAND_PWD):
            handleCommand(v->data[0], v->data);
            break;
        case (COMMAND_CLEAR):
            handleCommand(v->data[0], v->data);
            break;
        case (COMMAND_SAMFETCH):
            handleSamfetch();
            break;
        case (COMMAND_UNKNOWN):
            printf("Unknown Command\n");
            break;
        default:
            break;
      
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

    // set pointer to null again on stack
    destroyVector(&v);

    _exit(sig);
}
