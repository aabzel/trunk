

#ifndef SUPER_CYCLE_COMMANDS_H
#define SUPER_CYCLE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SUPER_CYCLE
#error "+HAS_SUPER_CYCLE"
#endif

#ifndef HAS_SUPER_CYCLE_DIAG
#error "+HAS_SUPER_CYCLE_DIAG"
#endif

#ifndef HAS_SUPER_CYCLE_COMMANDS
#error "+HAS_SUPER_CYCLE_COMMANDS"
#endif

bool super_cycle_init_command(int32_t argc, char* argv[]);
bool super_cycle_iteration_sleep_command(int32_t argc, char* argv[]);
bool super_cycle_diag_command(int32_t argc, char* argv[]);

#define SUPER_CYCLE_COMMANDS                                                                                                 \
    SHELL_CMD("super_cycle_iteration_sleep",  "scis",  super_cycle_iteration_sleep_command,   "SuperCycleIterationSleep"),   \
    SHELL_CMD("super_cycle_init",  "sci",  super_cycle_init_command,   "SuperCycleInit"),                                    \
    SHELL_CMD("super_cycle_diag",  "scd",  super_cycle_diag_command,   "SuperCycleDiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*SUPER_CYCLE_COMMANDS_H*/
