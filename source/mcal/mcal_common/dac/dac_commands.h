#ifndef DAC_COMMANDS_H
#define DAC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif /*HAS_DAC*/

#ifndef HAS_DAC_COMMANDS
#error "+HAS_DAC_COMMANDS"
#endif

bool dac_init_command(int32_t argc, char* argv[]);
bool dac_diag_command(int32_t argc, char* argv[]);
bool dac_code_command(int32_t argc, char* argv[]);
bool dac_voltage_command(int32_t argc, char* argv[]);

#define DAC_COMMANDS                                                                                                   \
    SHELL_CMD("dac_init", "daci", dac_init_command, "DacInit"),                                                        \
        SHELL_CMD("dac_diag", "dacd", dac_diag_command, "DacDiag"),                                                    \
        SHELL_CMD("dac_voltage", "dacv", dac_voltage_command, "DacVoltage"),         \
        SHELL_CMD("dac_code", "dacc", dac_code_command, "DacCode"),

#ifdef __cplusplus
}
#endif

#endif /* DAC_COMMANDS_H */
