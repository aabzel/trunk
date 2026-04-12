#ifndef SCHEDULER_COMMANDS_H
#define SCHEDULER_COMMANDS_H

#include "std_includes.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_SCHEDULER
#error "+HAS_SCHEDULER"
#endif

#ifndef HAS_SCHEDULER_COMMANDS
#error "+HAS_SCHEDULER_COMMANDS"
#endif

bool scheduler_task_period_command(int32_t argc, char* argv[]);
bool scheduler_ctrl_command(int32_t argc, char* argv[]);
bool scheduler_diag_command(int32_t argc, char* argv[]);
bool scheduler_diag_period_command(int32_t argc, char* argv[]);
bool scheduler_diag_run_command(int32_t argc, char* argv[]);
bool scheduler_init_command(int32_t argc, char* argv[]);

#define SCHEDULER_COMMANDS                                                            \
    SHELL_CMD("scheduler_task_period", "stp", scheduler_task_period_command, "TaskPeriod"),               \
    SHELL_CMD("scheduler_init", "ti", scheduler_init_command, "TaskInit"),               \
    SHELL_CMD("scheduler_ctrl", "tc", scheduler_ctrl_command, "TaskControl"),             \
    SHELL_CMD("scheduler_diag_periods", "tdp", scheduler_diag_period_command, "TaskDiagPeriod"),  \
    SHELL_CMD("scheduler_diag_run", "tdr", scheduler_diag_run_command, "TaskDiagRun"),     \
    SHELL_CMD("scheduler_diag", "tdi", scheduler_diag_command, "TaskDiag"),                \

#endif /* SCHEDULER_COMMANDS_H */
