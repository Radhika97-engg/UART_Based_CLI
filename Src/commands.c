#include "commands.h"
#include "uart.h"
#include <string.h>

/********** Command Buffer Management **********/
char command_buffer[MAX_BUFFER_SIZE];
uint8_t bufferIndex = 0;

/*************** Command Execution Function ***************/
void execute_command(char *cmd)
{
    // Debug: Print the received command
    for (int i = 0; cmd[i] != '\0'; i++)
    {
        uart2_write(cmd[i]);  // Print each character
    }
    uart2_write('\n');  // Newline for readability

    if (strcmp(cmd, "LED_ON") == 0)
    {
        uart2_write('O');
    }
    else if (strcmp(cmd, "LED_OFF") == 0)
    {
        uart2_write('F');
    }
    else if (strcmp(cmd, "STATUS") == 0)
    {
        uart2_write('S');
    }
    else
    {
        uart2_write('E');  // Unknown command error
    }

    memset(command_buffer, 0, MAX_BUFFER_SIZE);
    bufferIndex = 0;
}

/********** Function to Trim Newline Characters **********/
void trim_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\r' || str[len - 1] == '\n'))
    {
        str[len - 1] = '\0';
        uart2_write('T');   //Indicate trimming
    }
}
