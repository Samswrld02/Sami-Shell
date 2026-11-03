#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include "terminal.h"

// void _handleExit() {
//     printf("Goodbye");
// }



void handleCommandsParent(char* str, char** args) {
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