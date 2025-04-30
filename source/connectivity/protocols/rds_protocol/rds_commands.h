#ifndef RDS_COMMAND_H
#define RDS_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_RDS
#error "+HAS_RDS"
#endif

#ifndef HAS_RDS_COMMANDS
#error "+HAS_RDS_COMMANDS"
#endif

bool rds_diag_command(int32_t argc, char* argv[]);
bool rds_init_command(int32_t argc, char* argv[]);
bool rds_proc_command(int32_t argc, char* argv[]);

#define RDS_COMMANDS                                                                                                   \
    SHELL_CMD("rds_init", "rdsi", rds_init_command, "RdsInit"),                                                        \
        SHELL_CMD("rds_diag", "rdsd", rds_diag_command, "RdsDiag"),                                                    \
        SHELL_CMD("rds_proc", "rdsp", rds_proc_command, "RdsProc"),

#ifdef __cplusplus
}
#endif

#endif /* RDS_COMMAND_H */
