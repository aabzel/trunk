#ifndef ADC_GENERAL_COMMANDS_H
#define ADC_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_commands.h"
#else
#define ADC_CUSTOM_COMMANDS
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

bool adc_set_vref_command(int32_t argc, char* argv[]);
bool adc_init_command(int32_t argc, char* argv[]);
bool adc_diag_command(int32_t argc, char* argv[]);
bool adc_isr_command(int32_t argc, char* argv[]);
bool adc_start_command(int32_t argc, char* argv[]);

#define ADC_COMMANDS                                                                   \
    ADC_CUSTOM_COMMANDS                                                                \
    SHELL_CMD("adc_init", "ai", adc_init_command, "AdcInit"),                          \
    SHELL_CMD("adc_start", "at", adc_start_command, "AdcStart"),                          \
    SHELL_CMD("adc_isr", "as", adc_isr_command, "AdcIsrDiag"),                         \
    SHELL_CMD("adc_set_vref", "asvr", adc_set_vref_command, "AdcSetVref"),             \
    SHELL_CMD("adc_diag", "ad", adc_diag_command, "AdcDiag"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_GENERAL_COMMANDS_H */
