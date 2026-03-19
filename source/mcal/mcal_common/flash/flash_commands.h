#ifndef FLASH_COMMANDS_H
#define FLASH_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_commands.h"
#else
#define FLASH_CUSTOM_COMMANDS
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#ifndef HAS_STORAGE
#error "+HAS_STORAGE"
#endif

bool flash_diag_cmd(int32_t argc, char* argv[]);
bool flash_init_cmd(int32_t argc, char* argv[]);
bool flash_scan_cmd(int32_t argc, char* argv[]);
bool flash_read_cmd(int32_t argc, char* argv[]);
bool flash_write_cmd(int32_t argc, char* argv[]);
bool flash_erase_cmd(int32_t argc, char* argv[]);
bool flash_lock_cmd(int32_t argc, char* argv[]);
bool flash_get_spare_aligne_cmd(int32_t argc, char* argv[]);

#define FLASH_COMMANDS                                                                                            \
    FLASH_CUSTOM_COMMANDS                                                                                         \
    SHELL_CMD("flash_get_spare_aligne", "fgsa", flash_get_spare_aligne_cmd, "FlashGetSpareAligne"),               \
    SHELL_CMD("flash_lock", "fl", flash_lock_cmd, "FlashLock"),                                                   \
    SHELL_CMD("flash_diag", "fd", flash_diag_cmd, "FlashDiag"),                                                   \
    SHELL_CMD("flash_init", "fi", flash_init_cmd, "FlashInit"),                                                   \
    SHELL_CMD("flash_write", "fw", flash_write_cmd, "FlashWrite"),                                            \
    SHELL_CMD("flash_read", "fr", flash_read_cmd, "FlashRead"),                                               \
    SHELL_CMD("flash_erase", "fe", flash_erase_cmd, "FlashErase"),                                            \
    SHELL_CMD("flash_scan", "fs", flash_scan_cmd, "FlashScan"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_COMMANDS_H */
