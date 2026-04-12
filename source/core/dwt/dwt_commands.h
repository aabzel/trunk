#ifndef DWT_COMMANDS_H
#define DWT_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DWT
#error "+ HAS_DWT"
#endif

#ifndef HAS_DWT_COMMANDS
#error "+ HAS_DWT_COMMANDS"
#endif

bool dwt_diag_command(int32_t argc, char* argv[]);
bool dwt_init_command(int32_t argc, char* argv[]);
bool dwt_reg_map_command(int32_t argc, char* argv[]);

#define DWT_COMMANDS                                                                         \
        SHELL_CMD("dwt_diag", "dwtd", dwt_diag_command, "DwtDiag"),                           \
        SHELL_CMD("dwt_init", "dwti", dwt_init_command, "DwtInit"),                           \
        SHELL_CMD("dwt_reg_map", "dwtrm", dwt_reg_map_command, "DwtRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* DWT_COMMANDS_H */
