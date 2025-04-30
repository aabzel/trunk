#ifndef ADC_CUSTOM_COMMANDS_H
#define ADC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool adc_custom_diag_command(int32_t argc, char* argv[]);

#define ADC_CUSTOM_COMMANDS SHELL_CMD("adc_info", "adc", adc_custom_diag_command, "AdcCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_COMMANDS_H */
