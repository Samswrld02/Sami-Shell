#ifndef COMMANDS_H
#define COMMANDS_H
#include "hashtable.h"

typedef enum {
    COMMAND_LS,
    COMMAND_PWD,
    COMMAND_CLEAR,
    COMMAND_SAMFETCH,
    COMMAND_UNKNOWN,
    COMMAND_EXIT,
    COMMAND_CD,
    COMMAND_BINARY
} CommandType;

CommandType stringToCommand(char* str);

void handleCommandsParent(char* str, char** args, hash_table* ht);
// this is for external commands
void handleCommand(char* str, char** args);

#endif