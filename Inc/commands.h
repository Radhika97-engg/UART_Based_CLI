#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define MAX_BUFFER_SIZE 50

extern char command_buffer[MAX_BUFFER_SIZE];
extern uint8_t bufferIndex;

void execute_command(char *cmd);
void trim_newline(char *str);

#endif
