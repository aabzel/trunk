#ifndef SYSTICK_COMMANDS_H
#define SYSTICK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

#ifndef HAS_SYSTICK_COMMANDS
#error "+HAS_SYSTICK_COMMANDS"
#endif

bool systick_start_command(int32_t argc, char* argv[]);
bool systick_stop_command(int32_t argc, char* argv[]);
bool systick_set_load_command(int32_t argc, char* argv[]);
bool systick_diag_command(int32_t argc, char* argv[]);

#define SYSTICK_COMMANDS                                                                                       \
    SHELL_CMD("systick_diag",    "stkd",  systick_diag_command, "SysTickDiag"),                                     \
    SHELL_CMD("systick_start",   "stks",  systick_start_command, "SysTickStart"),                               \
    SHELL_CMD("systick_stop",    "stkp",  systick_stop_command, "SysTickStop"),                                 \
    SHELL_CMD("systick_set_load", "stksl", systick_set_load_command, "SysTickSetLoad"),

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_COMMANDS_H */
