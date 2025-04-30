#ifndef ANALOG_FILTER_COMMANDS_H
#define ANALOG_FILTER_COMMANDS_H

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

bool analog_filter_rc_calc_command(int32_t argc, char* argv[]);
bool analog_filter_cap_calc_command(int32_t argc, char* argv[]);
bool analog_filter_lc_calc_command(int32_t argc, char* argv[]);

#define ANALOG_FILTER_COMMANDS                                                                       \
    SHELL_CMD("analog_filter_cap_calc", "cc", analog_filter_cap_calc_command, "AnalogFilterCapCalc"),   \
    SHELL_CMD("analog_filter_rc_calc", "rc", analog_filter_rc_calc_command, "AnalogFilterRcCalc"),   \
    SHELL_CMD("analog_filter_lc_calc", "lcap", analog_filter_lc_calc_command, "AnalogFilterLcCalc"),

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_FILTER_COMMANDS_H  */
