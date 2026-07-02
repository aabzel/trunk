#ifndef CORTEX_M7_COMMANDS_H
#define CORTEX_M7_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool cortex_m7_exceptions_nmi_command(int32_t argc, char* argv[]);
bool cortex_m7_exceptions_command(int32_t argc, char* argv[]);
bool vector_table_command(int32_t argc, char* argv[]);
bool cortex_m7_diag_command(int32_t argc, char* argv[]);

#define CORTEX_M7_COMMANDS                                                                                         \
    SHELL_CMD("vector_table", "cm7vt", vector_table_command, "CortexM7vectorTable"),                               \
    SHELL_CMD("cortex_m7_exeption", "cm7ex", cortex_m7_exceptions_command, "CortexM7Exceptions"),                  \
    SHELL_CMD("cortex_m7_exeption_nmi", "cm7exn", cortex_m7_exceptions_nmi_command, "CortexM7ExceptionsNMI"),      \
    SHELL_CMD("cortex_m7_diag", "cm7d", cortex_m7_diag_command, "CortexM7diag"),

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M7_COMMANDS_H */
