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
         case (COMMAND_LS):
            // handleCommand(str, args);
            break;
        case (COMMAND_PWD):
            // handleCommand(str, args);
            break;
        case (COMMAND_CLEAR):
            // handleCommand(str, args);
            break;
        case (COMMAND_SAMFETCH):
            // handleSamfetch();
            break;
        case (COMMAND_CD):
            if (chdir(args[1]) == -1) {
                perror("error");
            };
            break;
        case (COMMAND_UNKNOWN):
            printf("Unknown Command\n");
            break;
        case (COMMAND_EXIT):
            handleExit(2);
            break;
    }

}