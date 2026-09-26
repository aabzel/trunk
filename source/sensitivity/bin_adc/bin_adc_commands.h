#ifndef BIN_ADC_COMMANDS_H
#define BIN_ADC_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_BIN_ADC_CUSTOM_COMMANDS
#include "bin_adc_custom_commands.h"
#else
#define BIN_ADC_CUSTOM_COMMANDS
#endif


#ifndef HAS_BIN_ADC
#error "+ HAS_BIN_ADC"
#endif

#ifndef HAS_BIN_ADC_COMMANDS
#error "+ HAS_BIN_ADC_COMMANDS"
#endif

bool bin_adc_show_sample_command(int32_t argc, char* argv[]);
bool bin_adc_diag_command(int32_t argc, char* argv[]);
bool bin_adc_init_command(int32_t argc, char* argv[]);

#define BIN_ADC_COMMANDS                                                                                \
        BIN_ADC_CUSTOM_COMMANDS                                                                         \
        SHELL_CMD("bin_adc_diag", "bad", bin_adc_diag_command, "BinAdcDiag"),                           \
        SHELL_CMD("bin_adc_init", "bai", bin_adc_init_command, "BinAdcInit"),                           \
        SHELL_CMD("bin_adc_show_sample", "bass", bin_adc_show_sample_command, "BinAdcShowSamples"),

#ifdef __cplusplus
}
#endif

#endif /* BIN_ADC_COMMANDS_H */
