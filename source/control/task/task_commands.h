#ifndef TASK_COMMANDS_H
#define TASK_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_TASK
#error "+HAS_TASK"
#endif

#ifndef HAS_TASK_COMMANDS
#error "+HAS_TASK_COMMANDS"
#endif

bool task_ctrl_command(int32_t argc, char* argv[]);
bool task_diag_command(int32_t argc, char* argv[]);
bool task_diag_period_command(int32_t argc, char* argv[]);
bool task_diag_run_command(int32_t argc, char* argv[]);
bool task_init_command(int32_t argc, char* argv[]);

#define TASK_COMMANDS                                                            \
    SHELL_CMD("task_clear", "tcl", task_init_command, "TaskInit"),               \
    SHELL_CMD("task_ctrl", "tcr", task_ctrl_command, "TaskControl"),             \
    SHELL_CMD("task_diag_periods", "tdp", task_diag_period_command, "TaskDiagPeriod"),  \
    SHELL_CMD("task_diag_run", "tdr", task_diag_run_command, "TaskDiagRun"),     \
    SHELL_CMD("task_diag", "tdi", task_diag_command, "TaskDiag"),                \

#endif /* TASK_COMMANDS_H */
