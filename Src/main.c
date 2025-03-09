#include "uart.h"
#include "commands.h"

int main(void)
{
    uart2_tx_init();  // Initialize UART

    while (1)
    {
        uart2_rx_int();  // Handle received characters and execute commands
    }
    return 0;
}
