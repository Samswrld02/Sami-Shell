#include "terminal.h"
#include "customString.h"
#include <stdio.h>
#include <string.h>
#include <vector.h>

#define MAX_BUF 1024

void start_terminal(int args, char **argv) {
    int number_of_args = args;
    char buff[MAX_BUF];

    while (1) {

        // take in charachters from stdin into buffer
        fgets(buff, MAX_BUF, stdin);
        
        vector* v = newVector();

        // create substring 
        createSubstring(v, buff, getStringLength(buff), ' ');

        for (int i = 0; i < v->length; i++) {
             printf(" %s", v->data[i]);
        }
    
    }
}

