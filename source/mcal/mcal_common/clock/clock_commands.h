#ifndef CLOCK_GENERAL_COMMANDS_H
#define CLOCK_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_CLOCK_CUSTOM_COMMANDS
#include "clock_custom_commands.h"
#else
#define CLOCK_CUSTOM_COMMANDS
#endif

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool clock_core_set_command(int32_t argc, char* argv[]);
bool clock_diag_command(int32_t argc, char* argv[]);
bool clock_hw_pause_command(int32_t argc, char* argv[]);
bool clock_init_command(int32_t argc, char* argv[]);
bool clock_sw_pause_command(int32_t argc, char* argv[]);
bool clock_up_time_command(int32_t argc, char* argv[]);
bool clock_mux_command(int32_t argc, char* argv[]);

#define CLOCK_COMMANDS                                                                   \
    CLOCK_CUSTOM_COMMANDS                                                                \
    SHELL_CMD("clock_core_set", "ccs", clock_core_set_command, "ClockCoreSet"),          \
    SHELL_CMD("clock_diag", "cld", clock_diag_command, "ClockDiag"),                     \
    SHELL_CMD("clock_hw_pause", "hwp", clock_hw_pause_command, "ClockHwPauseMs"),        \
    SHELL_CMD("clock_init", "cli", clock_init_command, "ClockInit"),                     \
    SHELL_CMD("clock_mux", "cmc", clock_mux_command, "ClockMux"),                        \
    SHELL_CMD("clock_sw_pause", "swp", clock_sw_pause_command, "ClockSwPauseMs"),        \
    SHELL_CMD("clock_up_time", "cut", clock_up_time_command, "ClockUpTime"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_GENERAL_COMMANDS_H */
