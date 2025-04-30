#ifndef RUNNING_LINE_COMMANDS_H
#define RUNNING_LINE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_RUNNING_LINE_DIAG
#error "+HAS_RUNNING_LINE_DIAG"
#endif

bool cmd_running_line_get(int32_t argc, char* argv[]);
bool cmd_running_line_diag(int32_t argc, char* argv[]);
bool cmd_running_line_init(int32_t argc, char* argv[]);
bool cmd_running_line_set_text(int32_t argc, char* argv[]);
bool cmd_running_line_set_prefix(int32_t argc, char* argv[]);
bool cmd_running_line_set_suffix(int32_t argc, char* argv[]);

#define RUNNING_LINE_COMMANDS                                                                          \
    SHELL_CMD("running_line_init", "rli", cmd_running_line_init, "RunningLineInit"),                   \
    SHELL_CMD("running_line_diag", "rld", cmd_running_line_diag, "RunningLineDiag"),                   \
    SHELL_CMD("running_line_get", "rlg", cmd_running_line_get, "RunningLineGet"),                      \
    SHELL_CMD("running_line_set_text", "rlst", cmd_running_line_set_text, "RunningLineSetText"),       \
    SHELL_CMD("running_line_set_prefix", "rlsp", cmd_running_line_set_prefix, "RunningLineSetPrefix"), \
    SHELL_CMD("running_line_set_suffix", "rlss", cmd_running_line_set_suffix, "RunningLineSetSuffix"),

#ifdef __cplusplus
}
#endif

#endif /* RUNNING_LINE_COMMANDS_H  */
