#ifndef WATCHDOG_CUSTOM_COMMANDS_H
#define WATCHDOG_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


bool watchdog_raw_reg_command(int32_t argc, char* argv[]);
bool watchdog_reg_map_command(int32_t argc, char* argv[]);

#define WATCHDOG_CUSTOM_COMMANDS                                                               \
    SHELL_CMD("watchdog_raw_reg", "wdrr", watchdog_raw_reg_command, "WatchDogRawReg"),         \
    SHELL_CMD("watchdog_reg_map", "wdrm", watchdog_reg_map_command, "WatchDogRegVals"),

#ifdef __cplusplus
}
#endif

#endif /* WATCHDOG_CUSTOM_COMMANDS_H */
