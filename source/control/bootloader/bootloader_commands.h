#ifndef BOOTLOADER_COMMANDS_H
#define BOOTLOADER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"



bool bootloader_reboot_command(int32_t argc, char* argv[]);
bool bootloader_diag_command(int32_t argc, char* argv[]);
bool bootloader_erase_app_command(int32_t argc, char* argv[]);
bool bootloader_jump_addr_command(int32_t argc, char* argv[]);
bool bootloader_launch_app_command(int32_t argc, char* argv[]);
bool bootloader_proc_command(int32_t argc, char* argv[]);

#define BOOTLOADER_COMMANDS                                                                                            \
    SHELL_CMD("bootloader_reboot", "breboot", bootloader_reboot_command, "BootLoaderReboot"),                                                \
    SHELL_CMD("bootloader_jump", "jm", bootloader_jump_addr_command, "BootLoaderJumpToAddress"),                                                \
    SHELL_CMD("bootloader_try_jump", "bp", bootloader_proc_command, "BootLoaderTryJumpApp"),                                                   \
    SHELL_CMD("bootloader_launch", "la", bootloader_launch_app_command, "BootLoaderLaunchApp"),                                              \
    SHELL_CMD("bootloader_erase_app", "ea", bootloader_erase_app_command, "BootLoaderEraseApplication"),                                     \
    SHELL_CMD("bootloader_diag", "bod", bootloader_diag_command, "BootLoaderDiag"),



#ifdef __cplusplus
}
#endif

#endif /* BOOTLOADER_COMMANDS_H */
