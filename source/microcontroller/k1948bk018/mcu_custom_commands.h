#ifndef K1948BK018_COMMANDS_H
#define K1948BK018_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_K1948BK018
#error "+HAS_K1948BK018"
#endif  /*HAS_K1948BK018*/

#ifndef HAS_K1948BK018_COMMANDS
#error "+HAS_K1948BK018_COMMANDS"
#endif  /*HAS_K1948BK018_COMMANDS*/

bool k1948bk018_diag_command(int32_t argc, char* argv[]);
bool mik32_launch_eeprom_command(int32_t argc, char* argv[]);

#define MCU_CUSTOM_COMMANDS                                                       \
    SHELL_CMD("k1948bk018_diag", "mikd", k1948bk018_diag_command, "Mik32Diag"),   \
    SHELL_CMD("mik32_launch_eeprom", "mile", mik32_launch_eeprom_command, "Mik32LaunchEeprom"),

#ifdef __cplusplus
}
#endif

#endif /* K1948BK018_COMMANDS_H */
