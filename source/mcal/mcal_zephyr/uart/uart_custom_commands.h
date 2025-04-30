#ifndef UART_CUSTOM_COMMANDS_H
#define UART_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_UART
#error "+HAS_UART"
#endif

bool uart_custom_diag_commands(int32_t argc, char* argv[]);

#define UART_CUSTOM_COMMANDS                                                                                                 \
        SHELL_CMD("uart_custom_diag", "ucd", uart_custom_diag_commands, "UartCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* UART_CUSTOM_COMMANDS_H */
