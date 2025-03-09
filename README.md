# UART-Based CLI for STM32
This project is a UART-based Command Line Interface (CLI) for the STM32F446RE microcontroller.

## Features
- Supports commands:
  - `LED_ON` → Turns on the LED.
  - `LED_OFF` → Turns off the LED.
  - `STATUS` → Returns status.
- Sends `'E'` for unknown commands.

## UART Configuration
- **Baud Rate:** 115200
- **TX Pin:** PA2
- **RX Pin:** PA3

## How to Use
1. Connect to the UART using PuTTY at 115200 baud rate.
2. Type commands and press Enter.

## Files
- `main.c` → Main control flow.
- `uart.c` & `uart.h` → UART handling.
- `commands.c` & `commands.h` → Command processing.