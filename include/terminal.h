#ifndef TERMINAL_H
#define TERMINAL_H 

void start_terminal(int args, char **argv);

typedef struct {
    char* args;
    int length;
} arguments;


#endif