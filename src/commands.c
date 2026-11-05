#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include "terminal.h"


void handleCommandsParent(char* str, char** args, hash_table* ht) {
    CommandType command = stringToCommand(str);

     //get string 
    switch (command) {
        case (COMMAND_CD):
            if (chdir(args[1]) == -1) {
                perror("error");
            };
            break;
        case (COMMAND_EXIT):
            handleExit(2);
            break;
        default:
            break;
    }

}