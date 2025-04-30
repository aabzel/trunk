#ifndef FILE_PC_COMMANDS_H
#define FILE_PC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_FILE_PC
#error "+HAS_FILE_PC"
#endif

#ifndef HAS_FILE_PC_COMMANDS
#error "+HAS_FILE_PC_COMMANDS"
#endif

bool file_pc_load_to_array_i8_command(int32_t argc, char* argv[]);
bool file_pc_open_command(int32_t argc, char* argv[]);
bool file_pc_close_command(int32_t argc, char* argv[]);
bool file_pc_realpath_command(int32_t argc, char* argv[]);

#define FILE_PC_COMMANDS                                                                      \
    SHELL_CMD("file_pc_realpath",  "fprp", file_pc_realpath_command, "FilePcRealPath"),      \
    SHELL_CMD("file_pc_load_array_i8",  "fplai8", file_pc_load_to_array_i8_command, "FilePcLoadArrayI8"), \
    SHELL_CMD("file_pc_open",  "fpo", file_pc_open_command, "FilePcOpen"),    \
    SHELL_CMD("file_pc_close",  "fpc", file_pc_close_command, "FilePcClose"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FILE_PC_COMMANDS_H*/

