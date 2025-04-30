#ifndef VOLTAGE_DIVIDER_COMMANDS_H
#define VOLTAGE_DIVIDER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#define "+HAS_DIAG"
#endif

#ifndef HAS_VOLTAGE_DIVIDER_DIAG
#define "+HAS_VOLTAGE_DIVIDER_DIAG"
#endif

bool voltage_divider_calc_command(int32_t argc, char* argv[]);

#define VOLTAGE_DIVIDER_COMMANDS                                                               \
    SHELL_CMD("voltage_divider_calc", "vc", voltage_divider_calc_command, "VoltageDividerCalc"),

#ifdef __cplusplus
}
#endif

#endif /* VOLTAGE_DIVIDER_COMMANDS_H  */
