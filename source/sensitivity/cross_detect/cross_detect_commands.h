
#ifndef CROSS_DETECT_COMMANDS_H
#define CROSS_DETECT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CROSS_DETECT_COMMANDS
#error "+HAS_CROSS_DETECT_COMMANDS"
#endif /*HAS_CROSS_DETECT_COMMANDS*/

bool cross_detect_init_command(int32_t argc, char* argv[]);
bool cross_detect_enable_command(int32_t argc, char* argv[]);
bool cross_detect_diag_command(int32_t argc, char* argv[]);
bool cross_detect_diag_lut_command(int32_t argc, char* argv[]);
bool cross_detect_period_command(int32_t argc, char* argv[]);
bool cross_detect_pin_diag_command(int32_t argc, char* argv[]);

#define CROSS_DETECT_COMMANDS                                                                         \
    SHELL_CMD("cross_detect_lut", "clu", cross_detect_diag_lut_command, "CrossDetectLut"),                \
    SHELL_CMD("cross_detect_period", "cpe", cross_detect_period_command, "CrossDetectPeriod"),                \
    SHELL_CMD("cross_detect_init", "cdi", cross_detect_init_command, "CrossDetectInit"),                \
    SHELL_CMD("cross_detect_en", "cde", cross_detect_enable_command, "CrossDetectEnable"),              \
    SHELL_CMD("cross_detect_pin_diag", "cdpd", cross_detect_pin_diag_command, "CrossDetectPinDiag"),    \
    SHELL_CMD("cross_detect_diag", "cdd", cross_detect_diag_command, "CrossDetectDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CROSS_DETECT_COMMANDS_H */
