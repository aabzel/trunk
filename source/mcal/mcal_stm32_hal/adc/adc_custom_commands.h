#ifndef ADC_CUSTOM_COMMANDS_H
#define ADC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_ADC_CUSTOM_COMMANDS
#error "+HAS_ADC_CUSTOM_COMMANDS"
#endif

#ifndef HAS_ADC
#error "+HAS_ADC"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool adc_custom_diag_command(int32_t argc, char* argv[]);
bool adc_custom_init_command(int32_t argc, char* argv[]);

#define ADC_CUSTOM_COMMANDS                                                           \
    SHELL_CMD("adc_custom_init", "acdi", adc_custom_init_command, "AdcCustomInit"),   \
    SHELL_CMD("adc_custom_diag", "adccd", adc_custom_diag_command, "AdcCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_COMMANDS_H */
