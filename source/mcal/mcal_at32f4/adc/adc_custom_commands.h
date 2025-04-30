#ifndef ADC_CUSTOM_COMMANDS_H
#define ADC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_ADC_COMMANDS
#error "+HAS_ADC_COMMANDS"
#endif

#ifndef HAS_ADC
#error "+HAS_ADC"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool adc_start_command(int32_t argc, char* argv[]);

#define ADC_CUSTOM_COMMANDS                                                     \
    SHELL_CMD("adc_start", "ast", adc_start_command, "AdcStart"),


#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_COMMANDS_H */
