
#ifndef TIME_COMMANDS_H
#define TIME_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#ifndef HAS_TIME_COMMANDS
#error "+HAS_TIME_COMMANDS"
#endif

bool time_diag_command(int32_t argc, char* argv[]);
bool time_time_command(int32_t argc, char* argv[]);
bool time_synchronize_command(int32_t argc, char* argv[]);
bool time_wait_command(int32_t argc, char* argv[]);

#define TIME_COMMANDS                                                                      \
    SHELL_CMD("time_diag",  "td", time_diag_command, "TimeDiag"),                          \
    SHELL_CMD("time_wait",  "tw", time_wait_command, "TimeWait"),                          \
    SHELL_CMD("time_synchronize",  "ts", time_synchronize_command, "TimeSynchronize"),     \
    SHELL_CMD("time_time", "time", time_time_command, "Time"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*TIME_COMMANDS_H*/

