#ifndef WDT_COMMANDS_H
#define WDT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool wdt_diag_command(int32_t argc, char* argv[]);
bool wdt_set_command(int32_t argc, char* argv[]);
bool wdt_ctrl_command(int32_t argc, char* argv[]);

#define IWDG_COMMANDS                                                                                                   \
    SHELL_CMD("iwd_diag", "iwd", wdt_diag_command, "iWatchdog diag"),                                                    \
    SHELL_CMD("iwd_ctrl", "iwc", wdt_ctrl_command, "iWatchdogCtrl"),                                                    \
        SHELL_CMD("iwd_set", "iws", wdt_set_command, "iWatchdogSet"),

#ifdef __cplusplus
}
#endif

#endif /* WDT_COMMANDS_H */
