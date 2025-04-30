#ifndef UART_CUSTOM_COMMANDS_H
#define UART_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool diag_page_uarts(ostream_t* stream);
bool cmd_uarts(int32_t argc, char* argv[]);

#define UART_CUSTOM_COMMANDS                                                                                          \
    SHELL_CMD("uarts", "u", cmd_uarts, "PrintUartStatistics"),

#ifdef __cplusplus
}
#endif

#endif /* UART_CUSTOM_COMMANDS_H */
