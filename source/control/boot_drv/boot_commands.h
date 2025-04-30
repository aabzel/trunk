#ifndef BOOT_COMMANDS_H
#define BOOT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool boot_reboot_command(int32_t argc, char* argv[]);
bool boot_diag_command(int32_t argc, char* argv[]);

#define BOOT_COMMANDS                                                       \
    SHELL_CMD("boot_reboot", "brb", boot_reboot_command, "BootReBoot"),     \
    SHELL_CMD("boot_diag", "bd", boot_diag_command, "BootDiag"),



#ifdef __cplusplus
}
#endif

#endif /* BOOT_COMMANDS_H */
