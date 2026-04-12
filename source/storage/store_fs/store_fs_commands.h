#ifndef STORE_FS_COMMANDS_H
#define STORE_FS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_STORE_FS
#error "+ HAS_STORE_FS"
#endif

#ifndef HAS_STORE_FS_COMMANDS
#error "+ HAS_STORE_FS_COMMANDS"
#endif

bool store_fs_delete_command(int32_t argc, char* argv[]);
bool store_fs_diag_command(int32_t argc, char* argv[]);
bool store_fs_init_command(int32_t argc, char* argv[]);
bool store_fs_get_command(int32_t argc, char* argv[]);
bool store_fs_set_command(int32_t argc, char* argv[]);

#define STORE_FS_COMMANDS                                                                             \
    SHELL_CMD("store_fs_delete", "se", store_fs_delete_command, "StoreFsDelete"),                     \
    SHELL_CMD("store_fs_diag", "sd", store_fs_diag_command, "StoreFsDiag"),                           \
    SHELL_CMD("store_fs_get", "sg", store_fs_get_command, "StoreFsGet"),                              \
    SHELL_CMD("store_fs_init", "sfi", store_fs_init_command, "StoreFsInit"),                          \
    SHELL_CMD("store_fs_set", "ss", store_fs_set_command, "StoreFsSet"),

#ifdef __cplusplus
}
#endif

#endif /* STORE_FS_COMMANDS_H */
