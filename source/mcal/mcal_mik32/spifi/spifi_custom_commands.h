#ifndef SPIFI_CUSTOM_COMMANDS_H
#define SPIFI_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPI*/

#ifndef HAS_SPIFI_COMMANDS
#error "+HAS_SPIFI_COMMANDS"
#endif /*HAS_SPIFI_COMMANDS*/

bool spifi_raw_reg_command(int32_t argc, char* argv[]);
bool spifi_custom_diag_command(int32_t argc, char* argv[]);
bool spifi_diag_low_level_command(int32_t argc, char* argv[]);
bool spifi_page_program_command(int32_t argc, char* argv[]);
bool spifi_reset_command(int32_t argc, char* argv[]);

#define SPIFI_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("spifi_reset", "sfr", spifi_reset_command, "SpiFiReset"),    \
    SHELL_CMD("spifi_page_program", "sfpp", spifi_page_program_command, "SpiFiPageProgram"),    \
    SHELL_CMD("spifi_diag_low_level", "sfdll", spifi_diag_low_level_command, "SpiFiDiagLowLev"),    \
    SHELL_CMD("spifi_raw_reg", "sfrr", spifi_raw_reg_command, "SpiFiRawReg"),                       \
    SHELL_CMD("spifi_custom_diag", "sfcd", spifi_custom_diag_command, "SpiFiCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* SPIFI_CUSTOM_COMMANDS_H */
