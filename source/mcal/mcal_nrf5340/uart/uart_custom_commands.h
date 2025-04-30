#ifndef UART_COSTOM_COMMANDS_H
#define UART_COSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#define UART_CUSTOM_COMMANDS

#if 0
bool uart_diag_low_level_command(int32_t argc, char* argv[]);
bool diag_page_uarts(ostream_t* stream);
bool cmd_uarts(int32_t argc, char* argv[]);
bool uart_send_command(int32_t argc, char* argv[]);
bool uart_set_baudrate_command(int32_t argc, char* argv[]);
bool uart_init_command(int32_t argc, char* argv[]);
bool uart_diag_command(int32_t argc, char* argv[]);
#define UART_CUSTOM_COMMANDS                                                                                                 \
    SHELL_CMD("uarts", "u", cmd_uarts, "PrintUartStatistics"),                                                        \
        SHELL_CMD("uart_init", "ui", uart_init_command, "UartInit"),                                                  \
        SHELL_CMD("uart_diag", "ud", uart_diag_command, "UartDiag"),                                                  \
        SHELL_CMD("uart_baud", "ub", uart_set_baudrate_command, "UartSetBaud"),                                       \
        SHELL_CMD("uart_diag_ll", "udl", uart_diag_low_level_command, "UartDiagLowLevel"),                            \
        SHELL_CMD("uart_send", "us", uart_send_command, "UartSend hex str"),
#endif

#ifdef __cplusplus
}
#endif

#endif /* UART_COSTOM_COMMANDS_H */
