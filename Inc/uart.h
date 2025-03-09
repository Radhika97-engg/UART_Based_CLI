#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32f446xx.h"

#define GPIOAEN        (1U << 0)     // Enable clock for GPIOA
#define UART2EN        (1U << 17)    // Enable clock for USART2

#define SYS_FREQ       16000000      // System frequency
#define APB1_CLK       SYS_FREQ
#define UART_BAUDRATE  115200        // Define baud rate

#define CR1_TE         (1U << 3)     // Transmitter Enable - Bit 3
#define CR1_RE         (1U << 2)     // Receiver Enable - Bit 2
#define CR1_UE         (1U << 13)    // UART Enable - Bit 13
#define SR_TXE         (1U << 7)     // TXE - Bit 7 (Transmit Data Register Empty)
#define SR_RXNE        (1U << 5)     // RXNE - Bit 5 (Read Data Register Not Empty)

#define MAX_BUFFER_SIZE 50  // Maximum command line size

void uart2_tx_init(void);
void uart2_write(int ch);
char uart2_rx_int(void);

#endif  // UART_H
