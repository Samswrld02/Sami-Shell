#ifndef COMMANDS_H
#define COMMANDS_H

typedef enum {
    COMMAND_LS,
    COMMAND_PWD,
    COMMAND_CLEAR,
    COMMAND_SAMFETCH,
    COMMAND_UNKNOWN,
    COMMAND_EXIT,
    COMMAND_CD,
} CommandType;

CommandType stringToCommand(char* str);

void handleCommandsParent(char* str, char** args);
// this is for external commands
void handleCommand(char* str, char** args);

#endif