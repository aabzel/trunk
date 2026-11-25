#ifndef CRYP_CUSTOM_COMMANDS_H
#define CRYP_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool cryp_interrupt_diag_command(int32_t argc, char* argv[]);

#define CRYP_CUSTOM_COMMANDS                                                                                                \
   SHELL_CMD("cryp_int_diag", "ccid", cryp_interrupt_diag_command, "CrypIntDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CRYP_CUSTOM_COMMANDS_H */
