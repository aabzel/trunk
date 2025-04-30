#ifndef TIMER_CUSTOM_COMMANDS_H
#define TIMER_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_TIMER_COMMANDS
#error "+HAS_TIMER_COMMANDS"
#endif

#ifndef HAS_TIMER
#error "+HAS_TIMER"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool timer_nrf_diag_compare_command(int32_t argc, char* argv[]);

#define TIMER_CUSTOM_COMMANDS                                                                                          \
    SHELL_CMD("timer_diag_compare", "tdc", timer_nrf_diag_compare_command, "TimerDiagComparator"),

#ifdef __cplusplus
}
#endif

#endif /* TIMER_CUSTOM_COMMANDS_H */
