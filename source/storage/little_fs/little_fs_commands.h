#ifndef LITTLE_FS_COMMANDS_H
#define LITTLE_FS_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_LITTLE_FS
#error "+ HAS_LITTLE_FS"
#endif

#ifndef HAS_LITTLE_FS_COMMANDS
#error "+ HAS_LITTLE_FS_COMMANDS"
#endif

bool little_fs_init_command(int32_t argc, char* argv[]);
bool little_fs_diag_command(int32_t argc, char* argv[]);
bool little_fs_remove_command(int32_t argc, char* argv[]);
bool little_fs_file_info_command(int32_t argc, char* argv[]) ;
bool little_fs_open_command(int32_t argc, char* argv[]);
bool little_fs_read_ll_command(int32_t argc, char* argv[]);
bool little_fs_read_command(int32_t argc, char* argv[]);
bool little_fs_write_command(int32_t argc, char* argv[]);
bool little_fs_write_ll_command(int32_t argc, char* argv[]);
bool little_fs_list_command(int32_t argc, char* argv[]);

#define LITTLE_FS_COMMANDS                                                                                    \
        SHELL_CMD("little_fs_remove", "lfrm", little_fs_remove_command, "LittleFsRemove"),                    \
        SHELL_CMD("little_fs_ls", "lfl", little_fs_list_command, "LittleFsList"),                    \
        SHELL_CMD("little_fs_file_info", "lffi", little_fs_file_info_command, "LittleFsFileInfo"),            \
        SHELL_CMD("little_fs_open", "lfo", little_fs_open_command, "LittleFsDiag"),                           \
        SHELL_CMD("little_fs_read_ll", "lfrl", little_fs_read_ll_command, "LittleFsReadLowLevel"),            \
        SHELL_CMD("little_fs_write_ll", "lfwl", little_fs_write_ll_command, "LittleFsWriteLowLevel"),         \
        SHELL_CMD("little_fs_read", "lfr", little_fs_read_command, "LittleFsRead"),                           \
        SHELL_CMD("little_fs_write", "lfw", little_fs_write_command, "LittleFsWrite"),                        \
        SHELL_CMD("little_fs_diag", "lfd", little_fs_diag_command, "LittleFsDiag"),                           \
        SHELL_CMD("little_fs_init", "lfi", little_fs_init_command, "LittleFsInit"),

#ifdef __cplusplus
}
#endif

#endif /* LITTLE_FS_COMMANDS_H */
