#ifndef WATCHDOG_COMMANDS_H
#define WATCHDOG_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "watchdog_custom_commands.h"

bool watchdog_ctrl_command(int32_t argc, char* argv[]);
bool watchdog_diag_command(int32_t argc, char* argv[]);
bool watchdog_set_command(int32_t argc, char* argv[]);

#define WATCHDOG_COMMANDS                                                         \
    WATCHDOG_CUSTOM_COMMANDS                                                      \
    SHELL_CMD("watchdog_ctrl", "wdc", watchdog_ctrl_command, "WatchDogCtrl"),     \
    SHELL_CMD("watchdog_diag", "wdd", watchdog_diag_command, "WatchDogDiag"),     \
    SHELL_CMD("watchdog_set", "wds", watchdog_set_command, "WatchDogSet"),

#ifdef __cplusplus
}
#endif

#endif /* WATCHDOG_COMMANDS_H */
