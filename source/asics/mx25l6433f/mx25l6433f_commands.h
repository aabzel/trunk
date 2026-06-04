#ifndef MX25L6433F_COMMANDS_H
#define MX25L6433F_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MX25L6433F
#error "+ HAS_MX25L6433F"
#endif

#ifndef HAS_MX25L6433F_COMMANDS
#error "+ HAS_MX25L6433F_COMMANDS"
#endif

bool mx25l6433f_diag_command(int32_t argc, char* argv[]);
bool mx25l6433f_init_command(int32_t argc, char* argv[]);
bool mx25l6433f_reg_map_command(int32_t argc, char* argv[]);

#define MX25L6433F_COMMANDS                                                                                          \
        SHELL_CMD("mx25l6433f_diag", "mx25d", mx25l6433f_diag_command, "Mx25l6433fDiag"),                           \
        SHELL_CMD("mx25l6433f_init", "mx25i", mx25l6433f_init_command, "Mx25l6433fInit"),                           \
        SHELL_CMD("mx25l6433f_reg_map", "mx25rm", mx25l6433f_reg_map_command, "Mx25l6433fRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_COMMANDS_H */
