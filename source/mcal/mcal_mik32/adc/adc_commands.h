#ifndef ADC_COMMANDS_H
#define ADC_COMMANDS_H

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

bool adc_read_command(int32_t argc, char* argv[]);
bool adc_diag_command(int32_t argc, char* argv[]);
bool adc_init_command(int32_t argc, char* argv[]);
bool adc_inputs_command(int32_t argc, char* argv[]);

#define ADC_COMMANDS                                                                                              \
    SHELL_CMD("adc_init", "adi", adc_init_command, "AdcInit"),                                                    \
    SHELL_CMD("adc_int", "ain", adc_inputs_command, "AdcIn"),                                                    \
    SHELL_CMD("adc_diag", "add", adc_diag_command, "AdcDiag"),                                                    \
    SHELL_CMD("adc_read", "adr", adc_read_command, "AdcRead"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_COMMANDS_H */
