#ifndef UART_COMMANDS_H
#define UART_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "debug_info.h"
#include "ostream.h"

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_UART_CUSTOM
#include "uart_custom_commands.h"
#else /*HAS_UART_CUSTOM*/
#define UART_CUSTOM_COMMANDS
#endif /*HAS_UART_CUSTOM*/

bool uart_diag_low_level_command(int32_t argc, char* argv[]) ;
bool uart_set_baudrate_command(int32_t argc, char* argv[]);
bool uart_send_command(int32_t argc, char* argv[]);
bool uart_wait_send_command(int32_t argc, char* argv[]);
bool uart_send_wait_command(int32_t argc, char* argv[]);
bool uart_init_command(int32_t argc, char* argv[]);
bool uart_diag_command(int32_t argc, char* argv[]);
bool uart_dma_send_command(int32_t argc, char* argv[]);

#define UART_COMMANDS    \
        UART_CUSTOM_COMMANDS                                                                  \
        SHELL_CMD("uart_baud", "ub", uart_set_baudrate_command, "UartSetBaud"),            \
        SHELL_CMD("uart_send", "us", uart_send_command, "UartSend"),              \
        SHELL_CMD("uart_dma_send", "udms", uart_dma_send_command, "UartDmaSend"),              \
        SHELL_CMD("uart_wait_send", "uws", uart_wait_send_command, "UartWaitSend"),              \
        SHELL_CMD("uart_send_wait", "usw", uart_send_wait_command, "UartSendWait"),              \
        SHELL_CMD("uart_init", "ui", uart_init_command, "UartInit"),                       \
        SHELL_CMD("uart_diag", "ud", uart_diag_command, "UartDiag"),         

#ifdef __cplusplus
}
#endif

#endif /* UART_COMMANDS_H */
