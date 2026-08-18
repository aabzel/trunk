#ifndef SA51034_COMMANDS_H
#define SA51034_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SA51034
#error "+ HAS_SA51034"
#endif

#ifndef HAS_SA51034_COMMANDS
#error "+ HAS_SA51034_COMMANDS"
#endif

bool sa51034_gain_command(int32_t argc, char* argv[]);
bool sa51034_reset_command(int32_t argc, char* argv[]);
bool sa51034_frequency_command(int32_t argc, char* argv[]);
bool sa51034_power_limit_command(int32_t argc, char* argv[]);
bool sa51034_diag_low_level_command(int32_t argc, char* argv[]);
bool sa51034_diag_hl_command(int32_t argc, char* argv[]);
bool sa51034_init_command(int32_t argc, char* argv[]);
bool sa51034_i2c_ping_command(int32_t argc, char* argv[]);
bool sa51034_reg_write_command(int32_t argc, char* argv[]);
bool sa51034_reg_read_command(int32_t argc, char* argv[]);
bool sa51034_reg_map_command(int32_t argc, char* argv[]);
bool sa51034_reg_hazy_command(int32_t argc, char* argv[]);

#define SA51034_COMMANDS                                                                                  \
        SHELL_CMD("sa51034_reset", "sar", sa51034_reset_command, "Sa51034Reset"),        \
        SHELL_CMD("sa51034_power_limit", "spl", sa51034_power_limit_command, "Sa51034PowerLimit"),        \
        SHELL_CMD("sa51034_ping", "sp", sa51034_i2c_ping_command, "Sa51034Ping"),        \
        SHELL_CMD("sa51034_map", "srm", sa51034_reg_map_command, "Sa51034RegMap"),        \
        SHELL_CMD("sa51034_frequency", "sf", sa51034_frequency_command, "Sa51034Freq"),        \
        SHELL_CMD("sa51034_gain", "sg", sa51034_gain_command, "Sa51034Gain"),        \
        SHELL_CMD("sa51034_hazy", "srh", sa51034_reg_hazy_command, "Sa51034RegHazy"),        \
        SHELL_CMD("sa51034_read", "sr", sa51034_reg_read_command, "Sa51034RegRead"),     \
        SHELL_CMD("sa51034_write", "sw", sa51034_reg_write_command, "Sa51034RegWrite"),  \
        SHELL_CMD("sa51034_diag_ll", "adl", sa51034_diag_low_level_command, "Sa51034DiagLowLevel"),             \
        SHELL_CMD("sa51034_diag_hi_lev", "sdh", sa51034_diag_hl_command, "Sa51034DiagHiLevel"),             \
        SHELL_CMD("sa51034_init", "sai", sa51034_init_command, "Sa51034Init"),


#ifdef __cplusplus
}
#endif

#endif /* SA51034_COMMANDS_H */
