#ifndef FLASH_FS_COMMANDS_H
#define FLASH_FS_COMMANDS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_flash_fs_diag(int32_t argc, char* argv[]);
bool cmd_flash_fs_toggle_page(int32_t argc, char* argv[]);
bool cmd_flash_fs_inval(int32_t argc, char* argv[]);
bool flash_dump_command(int32_t argc, char* argv[]);
bool cmd_flash_fs_format(int32_t argc, char* argv[]);

#define FLASH_FS_BASE_COMMANDS                                                                             \
    SHELL_CMD("flash_fs_diag", "ffd", cmd_flash_fs_diag, "FlashFsDiag"),                                  \
        SHELL_CMD("flash_dump", "ffm", flash_dump_command, "FlashFsDump"),                                 \
        SHELL_CMD("flash_fs_format", "fff", cmd_flash_fs_format, "FlashFsFormat"),                         \
        SHELL_CMD("flash_fs_inval", "ffi", cmd_flash_fs_inval, "FlashFsInval"),                       \
        SHELL_CMD("flash_fs_toggle_page", "fft", cmd_flash_fs_toggle_page, "FlashFsTogglePg"),

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_set(int32_t argc, char* argv[]);
bool cmd_flash_fs_scan(int32_t argc, char* argv[]);
bool cmd_flash_fs_init(int32_t argc, char* argv[]);
bool cmd_flash_fs_get_addr(int32_t argc, char* argv[]);
bool cmd_flash_fs_get(int32_t argc, char* argv[]);

#define FLASH_FS_EXTENDED_COMMANDS                                                                                   \
    SHELL_CMD("flash_fs_set", "ffs", cmd_flash_fs_set, "FlashFsSet"),                                                \
        SHELL_CMD("flash_fs_scan", "ffc", cmd_flash_fs_scan, "FlashFsScan"),                                         \
        SHELL_CMD("flash_fs_get", "ffg", cmd_flash_fs_get, "FlashFsGet"),                                            \
        SHELL_CMD("flash_fs_init", "ffin", cmd_flash_fs_init, "FlashFsInit"),                                        \
        SHELL_CMD("flash_fs_get_add", "fga", cmd_flash_fs_get_addr, "FlashFsGetAddrass"),

#else
#define FLASH_FS_EXTENDED_COMMANDS
#endif

#define FLASH_FS_COMMANDS                                                                                              \
    FLASH_FS_BASE_COMMANDS                                                                                             \
    FLASH_FS_EXTENDED_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* FLASH_FS_COMMANDS_H */
