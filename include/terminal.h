#ifndef TERMINAL_H
#define TERMINAL_H 

void start_terminal(int args, char **argv);

void handleExit(int sig);

typedef struct {
    char* args;
    int length;
} arguments;


#endif