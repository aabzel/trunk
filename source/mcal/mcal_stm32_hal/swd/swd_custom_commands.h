#ifndef SWD_COMMANDS_H
#define SWD_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool swd_diag_command(int32_t argc, char* argv[]);
bool swd_read_command(int32_t argc, char* argv[]);
bool swd_write_command(int32_t argc, char* argv[]);
bool swd_init_command(int32_t argc, char* argv[]);

#define SWD_COMMANDS                                                                                                   \
    SHELL_CMD("swd_diag", "sd", swd_diag_command, "SwdDiag"),                                                         \
    SHELL_CMD("swd_init", "swd", swd_init_command, "SwdInit"),                                                         \
      SHELL_CMD("swd_read", "sr", swd_read_command, "SwdRead"),                                                     \
        SHELL_CMD("swd_write", "sw", swd_write_command, "SwdWriteHexStr"),

#ifdef __cplusplus
}
#endif

#endif /* SWD_COMMANDS_H */
