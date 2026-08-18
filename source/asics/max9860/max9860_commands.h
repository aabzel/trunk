#ifndef MAX9860_COMMANDS_H
#define MAX9860_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MAX9860
#error "+ HAS_MAX9860"
#endif

#ifndef HAS_MAX9860_COMMANDS
#error "+ HAS_MAX9860_COMMANDS"
#endif

#ifdef HAS_MAX9860_DAC_COMMANDS
#include "max9860_dac_commands.h"
#else
#define MAX9860_DAC_COMMANDS
#endif

#ifdef HAS_MAX9860_ADC_COMMANDS
#include "max9860_adc_commands.h"
#else
#define MAX9860_ADC_COMMANDS
#endif

bool max9860_attenuation_command(int32_t argc, char* argv[]);
bool max9860_reg_write_command(int32_t argc, char* argv[]);
bool max9860_reg_read_command(int32_t argc, char* argv[]);
bool max9860_init_command(int32_t argc, char* argv[]);
bool max9860_reg_map_command(int32_t argc, char* argv[]);
bool max9860_diag_low_level_command(int32_t argc, char* argv[]);
bool max9860_diag_hl_command(int32_t argc, char* argv[]);
bool max9860_i2c_ping_command(int32_t argc, char* argv[]);
bool max9860_reset_command(int32_t argc, char* argv[]);
bool max9860_reg_map_hidden_command(int32_t argc, char* argv[]);

#define MAX9860_COMMANDS                                                                  \
     MAX9860_DAC_COMMANDS                                                                 \
     MAX9860_ADC_COMMANDS                                                                 \
        SHELL_CMD("max9860_ping", "mp", max9860_i2c_ping_command, "Max9860Ping"),        \
        SHELL_CMD("max9860_map", "mrm", max9860_reg_map_command, "Max9860RegMap"),        \
        SHELL_CMD("max9860_map_hidden", "mrh", max9860_reg_map_hidden_command, "Max9860RegMapHidden"),        \
        SHELL_CMD("max9860_read", "mrr", max9860_reg_read_command, "Max9860RegRead"),     \
        SHELL_CMD("max9860_write", "mrw", max9860_reg_write_command, "Max9860RegWrite"),  \
        SHELL_CMD("max9860_diag_ll", "mdl", max9860_diag_low_level_command, "Max9860DiagLowLevel"),             \
        SHELL_CMD("max9860_diag_hi_lev", "mdh", max9860_diag_hl_command, "Max9860DiagHiLevel"),             \
        SHELL_CMD("max9860_init", "mi", max9860_init_command, "Max9860Init"),             \
        SHELL_CMD("max9860_reset", "mt", max9860_reset_command, "Max9860Reset"),

#ifdef __cplusplus
}
#endif

#endif /* MAX9860_COMMANDS_H */
