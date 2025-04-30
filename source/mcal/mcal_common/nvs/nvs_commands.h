#ifndef NVS_COMMANDS_H
#define NVS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

bool nvs_init_command(int32_t argc, char* argv[]);
bool nvs_diag_command(int32_t argc, char* argv[]);
bool nvs_erase_command(int32_t argc, char* argv[]);
bool nvs_mcal_readcommand(int32_t argc, char* argv[]);
bool nvs_mcal_writecommand(int32_t argc, char* argv[]);
bool nvs_dump_command(int32_t argc, char* argv[]);

#define NVS_COMMANDS                                                   \
    SHELL_CMD("nvs_init", "nvsi", nvs_init_command, "NvsInit"),        \
    SHELL_CMD("nvs_dump", "nvsm", nvs_dump_command, "NvsDump"),        \
    SHELL_CMD("nvs_diag", "nvsd", nvs_diag_command, "NvsDiag"),        \
    SHELL_CMD("nvs_erase", "nvse", nvs_erase_command, "NvsErase"),     \
    SHELL_CMD("nvs_read", "nvsr", nvs_mcal_readcommand, "NvsRead"),        \
    SHELL_CMD("nvs_write", "nvsw", nvs_mcal_writecommand, "NvsWrite"),

#ifdef __cplusplus
}
#endif

#endif /* NVS_COMMANDS_H */
