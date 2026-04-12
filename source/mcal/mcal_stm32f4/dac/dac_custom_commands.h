#ifndef DAC_CUSTOM_COMMANDS_H
#define DAC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DAC_CUSTOM_COMMANDS
#error "+HAS_DAC_CUSTOM_COMMANDS"
#endif

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool dac_custom_read_command(int32_t argc, char* argv[]);
bool dac_custom_diag_command(int32_t argc, char* argv[]);
bool dac_custom_init_command(int32_t argc, char* argv[]);
//bool dac_custom_inputs_command(int32_t argc, char* argv[]);
//    SHELL_CMD("dac_custom_int", "acin", dac_custom_inputs_command, "DacCustomIn"),

#define DAC_CUSTOM_COMMANDS                                                           \
    SHELL_CMD("dac_custom_init", "acdi", dac_custom_init_command, "DacCustomInit"),   \
    SHELL_CMD("dac_custom_diag", "acdd", dac_custom_diag_command, "DacCustomDiag"),   \
    SHELL_CMD("dac_custom_read", "acdr", dac_custom_read_command, "DacCustomRead"),

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_COMMANDS_H */
