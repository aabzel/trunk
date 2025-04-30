#ifndef CLOCK_DIVIDER_COMMANDS_H
#define CLOCK_DIVIDER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool clock_divider_n_command(int32_t argc, char* argv[]);
bool clock_divider_diag_command(int32_t argc, char* argv[]);

#define CLOCK_DIVIDER_COMMANDS                                                   \
    SHELL_CMD("clock_divider_n", "cdn", clock_divider_n_command, "ClockDivider"),           \
    SHELL_CMD("clock_divider_diag", "cdd", clock_divider_diag_command, "ClockDividerDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*CLOCK_DIVIDER_COMMANDS_H*/
