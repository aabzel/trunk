#ifndef WATCHDOG_CUSTOM_COMMANDS_H
#define WATCHDOG_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool wdt_diag_reg_command(int32_t argc, char* argv[]);

#define WATCHDOG_CUSTOM_COMMANDS                                            \
    SHELL_CMD("wdt_diag_reg", "wdr", wdt_diag_reg_command, "WatchDogRegs"),

#ifdef __cplusplus
}
#endif

#endif /* WATCHDOG_CUSTOM_COMMANDS_H */
