#ifndef DAC_COMMANDS_H
#define DAC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif

#ifndef HAS_DAC_COMMANDS
#error "+HAS_DAC_COMMANDS"
#endif

bool dac_init_command(int32_t argc, char* argv[]);
bool dac_diag_command(int32_t argc, char* argv[]);

#define DAC_COMMANDS                                                             \
    SHELL_CMD("dac_init", "daci", dac_init_command, "DacInit"),                  \
    SHELL_CMD("dac_diag", "dacd", dac_diag_command, "DacDiag"),

#ifdef __cplusplus
}
#endif

#endif /* DAC_COMMANDS_H */
