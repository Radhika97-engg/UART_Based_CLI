#include "uart.h"
#include "commands.h"
#include <string.h>

/********** Static Function Prototypes **********/
static uint16_t compute_uart_br(uint32_t periph_clk, uint32_t baud_rate);
static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baud_rate);

/********** UART Initialization **********/
void uart2_tx_init()
{
    RCC->AHB1ENR |= GPIOAEN;         // Enable GPIOA clock
    RCC->APB1ENR |= UART2EN;         // Enable USART2 clock

    // Configuring PA2 as UART_TX (Alternate Function 7)
    GPIOA->MODER &= ~(1U << 4);
    GPIOA->MODER |= (1U << 5);
    GPIOA->AFR[0] |= (1U << 8) | (1U << 9) | (1U << 10);
    GPIOA->AFR[0] &= ~(1U << 11);

    // Configuring PA3 as UART_RX (Alternate Function 7)
    GPIOA->MODER &= ~(1U << 6);
    GPIOA->MODER |= (1U << 7);
    GPIOA->AFR[0] |= (1U << 12) | (1U << 13) | (1U << 14);
    GPIOA->AFR[0] &= ~(1U << 15);

    USART2->CR1 |= CR1_TE | CR1_RE | CR1_UE;  // Enable TX, RX, and UART

    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
}

/********** UART Write Function **********/
void uart2_write(int ch)
{
    while (!(USART2->SR & SR_TXE));
    USART2->DR = ch & 0xFF;
}

/************** UART Read Function **************/
char uart2_rx_int(void)
{
    if (USART2->SR & SR_RXNE)
    {
        char received = USART2->DR;
        uart2_write(received);  // Debug: Echo received character

        if (received == '\n' || received == '\r')
        {
            command_buffer[bufferIndex] = '\0';
            trim_newline(command_buffer);         // Clean up the command
            execute_command(command_buffer);      // Execute cleaned command
        }
        else if (bufferIndex < MAX_BUFFER_SIZE - 1)
        {
            command_buffer[bufferIndex++] = received;
        }
        else
        {
            uart2_write('E');
            memset(command_buffer, 0, MAX_BUFFER_SIZE);
            bufferIndex = 0;
        }
        return received;
    }
    return '\0';
}

/********** Compute Baud Rate Register (BRR) Value **********/
static uint16_t compute_uart_br(uint32_t periph_clk, uint32_t baud_rate)
{
    return ((periph_clk + (baud_rate / 2U)) / baud_rate);
}

static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baud_rate)
{
    USARTx->BRR = compute_uart_br(periph_clk, baud_rate);
}
