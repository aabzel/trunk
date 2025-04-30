#ifndef UART_COMMANDS_H
#define UART_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool diag_page_uarts(ostream_t* stream);
bool cmd_uarts(int32_t argc, char* argv[]);
bool uart_send_command(int32_t argc, char* argv[]);
bool uart_init_command(int32_t argc, char* argv[]);
bool uart_diag_command(int32_t argc, char* argv[]);

#define UART_COMMANDS                                                                                                  \
    SHELL_CMD("uarts", "u", cmd_uarts, "Print UARTs statistics"),                                                      \
        SHELL_CMD("uart_init", "ui", uart_init_command, "UART init"),                                                  \
        SHELL_CMD("uart_diag", "ud", uart_diag_command, "UART diag"),                                                  \
        SHELL_CMD("uart_send", "us", uart_send_command, "UART send hex str"),

#ifdef __cplusplus
}
#endif

#endif /* UART_COMMANDS_H */
