#ifndef BOOT_COMMANDS_H
#define BOOT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool boot_reboot_command(int32_t argc, char* argv[]);
bool boot_diag_command(int32_t argc, char* argv[]);
bool boot_seek_command(int32_t argc, char* argv[]);
bool boot_init_command(int32_t argc, char* argv[]);
bool boot_stack_paint_command(int32_t argc, char* argv[]);

#define BOOT_COMMANDS                                                                 \
    SHELL_CMD("boot_stack_paint", "bsp", boot_stack_paint_command, "BootStackPaint"), \
    SHELL_CMD("boot_seek", "bs", boot_seek_command, "BootSeek"),            \
    SHELL_CMD("boot_init", "bi", boot_init_command, "BootInit"),            \
    SHELL_CMD("boot_reboot", "brb", boot_reboot_command, "BootReBoot"),     \
    SHELL_CMD("boot_diag", "bd", boot_diag_command, "BootDiag"),



#ifdef __cplusplus
}
#endif

#endif /* BOOT_COMMANDS_H */
