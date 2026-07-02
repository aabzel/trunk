#ifndef ADC_CHANNEL_CUSTOM_COMMANDS_H
#define ADC_CHANNEL_CUSTOM_COMMANDS_H

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

bool adc_custom_in_diag(char* key_word1, char* key_word2);
bool adc_custom_read_command(int32_t argc, char* argv[]);
//bool adc_custom_inputs_command(int32_t argc, char* argv[]);
//    SHELL_CMD("adc_custom_int", "acin", adc_custom_inputs_command, "AdcCustomIn"),

#define ADC_CHANNEL_CUSTOM_COMMANDS                                                           \
    SHELL_CMD("adc_custom_read", "acdr", adc_custom_read_command, "AdcCustomRead"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_COMMANDS_H */
