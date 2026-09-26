#ifndef BIN_DAC_COMMANDS_H
#define BIN_DAC_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_BIN_DAC_CUSTOM_COMMANDS
#include "bin_dac_custom_commands.h"
#else
#define BIN_DAC_CUSTOM_COMMANDS
#endif


#ifndef HAS_BIN_DAC
#error "+ HAS_BIN_DAC"
#endif

#ifndef HAS_BIN_DAC_COMMANDS
#error "+ HAS_BIN_DAC_COMMANDS"
#endif

bool bin_dac_show_sample_command(int32_t argc, char* argv[]) ;
bool bin_dac_diag_command(int32_t argc, char* argv[]);
bool bin_dac_init_command(int32_t argc, char* argv[]);

#define BIN_DAC_COMMANDS                                                                                \
        BIN_DAC_CUSTOM_COMMANDS                                                                         \
        SHELL_CMD("bin_dac_show_sample", "bdss", bin_dac_show_sample_command, "BinDacShowSamples"),     \
        SHELL_CMD("bin_dac_diag", "bdd", bin_dac_diag_command, "BinDacDiag"),                           \
        SHELL_CMD("bin_dac_init", "bdi", bin_dac_init_command, "BinDacInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* BIN_DAC_COMMANDS_H */
