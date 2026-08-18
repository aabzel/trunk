#ifndef NAU8814_COMMANDS_H
#define NAU8814_COMMANDS_H

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

#ifdef HAS_NAU8814_DAC_COMMANDS
#include "nau8814_dac_commands.h"
#else
#define NAU8814_DAC_COMMANDS
#endif

#ifdef HAS_NAU8814_ADC_COMMANDS
#include "nau8814_adc_commands.h"
#else
#define NAU8814_ADC_COMMANDS
#endif

bool nau8814_reg_map_hidden_command(int32_t argc, char* argv[]) ;
bool nau8814_attenuation_command(int32_t argc, char* argv[]);
bool nau8814_diag_low_level_command(int32_t argc, char* argv[]);
bool nau8814_diag_hl_command(int32_t argc, char* argv[]);
bool nau8814_calc_pll_command(int32_t argc, char* argv[]);
bool nau8814_init_command(int32_t argc, char* argv[]);
bool nau8814_i2c_ping_command(int32_t argc, char* argv[]);
bool nau8814_reg_write_command(int32_t argc, char* argv[]);
bool nau8814_reg_read_command(int32_t argc, char* argv[]);
bool nau8814_reg_map_command(int32_t argc, char* argv[]);
bool nau8814_reg_hazy_command(int32_t argc, char* argv[]);
bool nau8814_reset_command(int32_t argc, char* argv[]);

#define NAU8814_COMMANDS                                                                  \
     NAU8814_DAC_COMMANDS                                                                 \
     NAU8814_ADC_COMMANDS                                                                 \
        SHELL_CMD("nau8814_calc_pll", "ncp", nau8814_calc_pll_command, "Nau8814CalcPll"),        \
        SHELL_CMD("nau8814_ping", "nap", nau8814_i2c_ping_command, "Nau8814Ping"),        \
        SHELL_CMD("nau8814_map", "nrm", nau8814_reg_map_command, "Nau8814RegMap"),        \
        SHELL_CMD("nau8814_hazy", "nrh", nau8814_reg_hazy_command, "Nau8814RegHazy"),        \
        SHELL_CMD("nau8814_read", "nrr", nau8814_reg_read_command, "Nau8814RegRead"),     \
        SHELL_CMD("nau8814_write", "nrw", nau8814_reg_write_command, "Nau8814RegWrite"),  \
        SHELL_CMD("nau8814_diag_ll", "ndl", nau8814_diag_low_level_command, "Nau8814DiagLowLevel"),             \
        SHELL_CMD("nau8814_diag_hi_lev", "ndh", nau8814_diag_hl_command, "Nau8814DiagHiLevel"),             \
        SHELL_CMD("nau8814_init", "ni", nau8814_init_command, "Nau8814Init"),             \
        SHELL_CMD("nau8814_reset", "nt", nau8814_reset_command, "Nau8814Reset"),

#ifdef __cplusplus
}
#endif

#endif /* NAU8814_COMMANDS_H */
