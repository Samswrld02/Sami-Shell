#include "terminal.h"
#include "customString.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "vector.h"

#define MAX_BUF 1024

static vector* v  = NULL;

void handleExit(int sig);

void start_terminal(int args, char **argv) {
    int number_of_args = args;
    char buff[MAX_BUF];

    v = newVector();
    signal(SIGINT, handleExit);

    while (1) {
        v->length = 0;
        
        printf("Sami-shell> ");
        // take in charachters from stdin into buffer
        fgets(buff, MAX_BUF, stdin);
        
        
        // create substring 
        createSubstring(v, buff, getStringLength(buff), ' ');

        for (int i = 0; i < v->length; i++) {
             printf("%s ", v->data[i]);
        }
        printf("\n");

    }
}


void handleExit(int sig) {
    char msg[] = "\ngoodbye from sami :)\n";
    write(STDOUT_FILENO, msg, sizeof(msg));

    // set pointer to null again on stack
    destroyVector(&v);

    _exit(sig);
}
