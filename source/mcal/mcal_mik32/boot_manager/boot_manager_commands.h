#ifndef BOOT_MANAGER_COMMANDS_H
#define BOOT_MANAGER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_BOOT_MANAGER
#error "+HAS_BOOT_MANAGER"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool boot_manager_diag_command(int32_t argc, char* argv[]);

#define BOOT_MANAGER_COMMANDS                                                         \
    SHELL_CMD("boot_manager_diag", "bmd", boot_manager_diag_command, "BootManagerDiag"),

#ifdef __cplusplus
}
#endif

#endif /* BOOT_MANAGER_COMMANDS_H */
