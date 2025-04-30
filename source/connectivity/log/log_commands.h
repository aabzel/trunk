#ifndef LOG_COMMANDS_H
#define LOG_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

bool cmd_log_init(int32_t argc, char* argv[]);
bool cmd_log_level(int32_t argc, char* argv[]);
bool cmd_log_diag(int32_t argc, char* argv[]);

#ifdef HAS_LOG_EXT_CMD

bool cmd_log_color(int32_t argc, char* argv[]);
bool cmd_log_flush(int32_t argc, char* argv[]);
bool cmd_log_try_color(int32_t argc, char* argv[]);

#define LOG_COMMANDS_EXT                                         \
    SHELL_CMD("log_flush", "lf", cmd_log_flush, "LogFlush"),      \
    SHELL_CMD("log_color", "lc", cmd_log_color, "LogColor"), \
    SHELL_CMD("log_try_color", "ltc", cmd_log_try_color, "LogTryColor"),
#else
#define LOG_COMMANDS_EXT
#endif /*HAS_LOG_EXT_CMD*/

#define LOG_COMMANDS                                                       \
    SHELL_CMD("log_init", "li", cmd_log_init, "LogInit"),    \
    SHELL_CMD("log_level", "ll", cmd_log_level, "SetOrPrintLogLevels"),    \
    SHELL_CMD("log_diag", "ld", cmd_log_diag, "LogDiag"),                  \
    LOG_COMMANDS_EXT

#endif /*LOG_COMMANDS_H*/
