#ifndef DISK_COMMANDS_H
#define DISK_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DISK
#error "+ HAS_DISK"
#endif

#ifndef HAS_DISK_COMMANDS
#error "+ HAS_DISK_COMMANDS"
#endif

bool disk_diag_command(int32_t argc, char* argv[]);
bool disk_init_command(int32_t argc, char* argv[]);

#define DISK_COMMANDS                                                                           \
        SHELL_CMD("disk_diag", "did", disk_diag_command, "DiskDiag"),                           \
        SHELL_CMD("disk_init", "dii", disk_init_command, "DiskInit"),

#ifdef __cplusplus
}
#endif

#endif /* DISK_COMMANDS_H */
