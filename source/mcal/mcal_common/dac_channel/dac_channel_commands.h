#ifndef DAC_CHANNEL_GENERAL_COMMANDS_H
#define DAC_CHANNEL_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_DAC_CHANNEL_CUSTOM
#include "dac_channel_custom_commands.h"
#else
#define DAC_CHANNEL_CUSTOM_COMMANDS
#endif

#ifndef HAS_DAC_COMMANDS
#error "+HAS_DAC_COMMANDS"
#endif

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool dac_channel_code_set_command(int32_t argc, char* argv[]);
bool dac_channel_voltage_set_command(int32_t argc, char* argv[]);
bool dac_channel_diag_command(int32_t argc, char* argv[]);
bool dac_channel_isr_command(int32_t argc, char* argv[]);

#define DAC_CHANNEL_COMMANDS                                                                   \
    DAC_CHANNEL_CUSTOM_COMMANDS                                                                \
    SHELL_CMD("dac_channel_diag", "dachd", dac_channel_diag_command, "DacChannelDiag"),          \
    SHELL_CMD("dac_channel_voltage_set", "dcvs", dac_channel_voltage_set_command, "DacChannelVoltageSet"),  \
    SHELL_CMD("dac_channel_code_read", "dccs", dac_channel_code_set_command, "DacChannelCodeRead"),

#ifdef __cplusplus
}
#endif

#endif /* DAC_GENERAL_COMMANDS_H */
