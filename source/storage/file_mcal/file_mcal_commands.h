#ifndef FILE_MCAL_COMMANDS_H
#define FILE_MCAL_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_FILE_MCAL_CUSTOM_COMMANDS
#include "file_mcal_custom_commands.h"
#else
#define FILE_MCAL_CUSTOM_COMMANDS
#endif


#ifndef HAS_FILE_MCAL
#error "+ HAS_FILE_MCAL"
#endif

#ifndef HAS_FILE_MCAL_COMMANDS
#error "+ HAS_FILE_MCAL_COMMANDS"
#endif

bool rename_file_command(int32_t argc, char* argv[]);
bool file_mcal_diag_command(int32_t argc, char* argv[]);
bool file_mcal_init_command(int32_t argc, char* argv[]);
 
#define FILE_MCAL_COMMANDS                                                                                    \
        FILE_MCAL_CUSTOM_COMMANDS                                                                             \
        SHELL_CMD("rename_file", "rn", rename_file_command, "ReNameFile"),                                    \
        SHELL_CMD("file_mcal_diag", "fmd", file_mcal_diag_command, "FileMcalDiag"),                           \
        SHELL_CMD("file_mcal_init", "fmi", file_mcal_init_command, "FileMcalInit"),
 
#ifdef __cplusplus
}
#endif

#endif /* FILE_MCAL_COMMANDS_H */
