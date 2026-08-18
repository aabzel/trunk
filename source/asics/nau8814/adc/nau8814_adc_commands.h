#ifndef NAU8814_ADC_COMMANDS_H
#define NAU8814_ADC_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_NAU8814
#error "+ HAS_NAU8814"
#endif

#ifndef HAS_NAU8814_COMMANDS
#error "+ HAS_NAU8814_COMMANDS"
#endif

bool nau8814_listen_command(int32_t argc, char* argv[]);
bool nau8814_adc_diag_command(int32_t argc, char* argv[]);

#define NAU8814_ADC_COMMANDS                                                                         \
        SHELL_CMD("nau8814_listen", "nal", nau8814_listen_command, "Nau8814Listen"),    \
        SHELL_CMD("nau8814_adc_diag", "nad", nau8814_adc_diag_command, "Nau8814AdcDiag"),

#ifdef __cplusplus
}
#endif

#endif /* NAU8814_ADC_COMMANDS_H */


