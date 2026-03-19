#ifndef NVS_COMMANDS_H
#define NVS_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_NVS
#error "+ HAS_NVS"
#endif

#ifndef HAS_NVS_COMMANDS
#error "+ HAS_NVS_COMMANDS"
#endif

bool nvs_diag_command(int32_t argc, char* argv[]);
bool nvs_init_command(int32_t argc, char* argv[]);
bool nvs_read_command(int32_t argc, char* argv[]);
bool nvs_erase_command(int32_t argc, char* argv[]);
bool nvs_write_command(int32_t argc, char* argv[]);
bool nvs_dump_command(int32_t argc, char* argv[]);

#define NVS_COMMANDS                                                       \
        SHELL_CMD("nvs_diag", "nvd", nvs_diag_command, "NvsDiag"),          \
        SHELL_CMD("nvs_init", "ni", nvs_init_command, "NvsInit"),          \
        SHELL_CMD("nvs_dump", "nm", nvs_dump_command, "NvsDump"),          \
        SHELL_CMD("nvs_erase", "nve", nvs_erase_command, "NvsErase"),       \
        SHELL_CMD("nvs_read", "nr", nvs_read_command, "NvsRead"),          \
        SHELL_CMD("nvs_write", "nw", nvs_write_command, "NvsWrite"),

#ifdef __cplusplus
}
#endif

#endif /* NVS_COMMANDS_H */
