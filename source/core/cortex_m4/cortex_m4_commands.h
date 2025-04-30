#ifndef CORTEX_M4_COMMANDS_H
#define CORTEX_M4_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"

bool cortex_m4_coproc_access_command(int32_t argc, char* argv[]);
bool cortex_m4_exceptions_nmi_command(int32_t argc, char* argv[]);
bool cortex_m4_diag_command(int32_t argc, char* argv[]);
bool cortex_m4_exceptions_command(int32_t argc, char* argv[]);
bool cortex_m4_vector_table_command(int32_t argc, char* argv[]);
bool cortex_m4_breakpoints_command(int32_t argc, char* argv[]);

#define CORTEX_M4_COMMANDS                                                                                     \
    SHELL_CMD("cortex_m4_coproc_access", "cm4cop", cortex_m4_coproc_access_command, "CortexM4CoProcAccess"),                  \
    SHELL_CMD("cortex_m4_breakpoints", "cm4br", cortex_m4_breakpoints_command, "CortexM4BreakPoints"),         \
    SHELL_CMD("vector_table", "cm4vt", cortex_m4_vector_table_command, "CortexM4VectorTable"),                 \
    SHELL_CMD("cortex_m4_exeption", "cm4ex", cortex_m4_exceptions_command, "CortexM4Exceptions"),              \
    SHELL_CMD("cortex_m4_exeption_nmi", "cm4exn", cortex_m4_exceptions_nmi_command, "CortexM4ExceptionsNMI"),  \
    SHELL_CMD("core_diag", "cm4d", cortex_m4_diag_command, "CortexM4Diag"),

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M4_COMMANDS_H */
