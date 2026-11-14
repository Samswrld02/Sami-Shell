#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include "terminal.h"


int handleCommandsParent(Arena* arena, char* str, char** args) {
    CommandType command = stringToCommand(str);
    char buf[100];

    int executed = 0;

     //get string 
    switch (command) {
        case (COMMAND_CD):
            if (chdir(args[1]) == -1) {
                perror("error");
            };
            getcwd(buf, 100);
            printf("\n%s\n", buf);
            executed = 1;
            break;
        case (COMMAND_EXIT):
            handleExit(2);
            break;
        default:
            break;
    }

    // return 0 if command has not been handled by parent
    return executed;
}