#include "customString.h"
#include "vector.h"
#include <unistd.h>

// create substring based on delimiter
void createSubstring(vector* v, char* string, int length,  char delimiter){
    //set start value 
    int start = 0;

    for (int i = 0; i < length; i++) {
        if (string[i] == delimiter || string[i] == '\n') {
            // append starting pointer of string
            vectorAppend(v, &string[start]);
            string[i] = '\0';
           
            // reset pointer adress to new start
            start = i + 1;
        }
    }
}

int getStringLength(char* string) {
    int i = 0;

    while (string[i] != '\0') {
        i++;
    }

    return i;
}

int checkBinary(char* string) {
    // X_OK checks for execute permission
    if (access(string, X_OK) == 0) {
        return 1; // File is executable
    }
    return 0; // File does not exist or is not executable
}