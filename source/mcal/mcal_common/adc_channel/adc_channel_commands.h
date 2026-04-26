#ifndef ADC_CHANNEL_GENERAL_COMMANDS_H
#define ADC_CHANNEL_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_ADC_CHANNEL_CUSTOM
#include "adc_custom_commands.h"
#else
#define ADC_CHANNEL_CUSTOM_COMMANDS
#endif

#ifndef HAS_ADC_COMMANDS
#error "+HAS_ADC_COMMANDS"
#endif

#ifndef HAS_ADC
#error "+HAS_ADC"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool adc_voltage_read_command(int32_t argc, char* argv[]);
bool adc_diag_command(int32_t argc, char* argv[]);
bool adc_channel_diag_command(int32_t argc, char* argv[]);
bool adc_isr_command(int32_t argc, char* argv[]);

#define ADC_CHANNEL_COMMANDS                                                                   \
    ADC_CHANNEL_CUSTOM_COMMANDS                                                                \
    SHELL_CMD("adc_channel_diag", "acd", adc_channel_diag_command, "AdcChannelDiag"),  \
    SHELL_CMD("adc_voltage_read", "avr", adc_voltage_read_command, "AdcVoltageRead"),  \
    SHELL_CMD("adc_code_read", "acr", adc_code_read_command, "AdcCodeRead"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_GENERAL_COMMANDS_H */
