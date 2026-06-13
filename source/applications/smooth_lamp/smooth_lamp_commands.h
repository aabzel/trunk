#ifndef SMOOTH_LAMP_COMMANDS_H
#define SMOOTH_LAMP_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SMOOTH_LAMP
#error "+ HAS_SMOOTH_LAMP"
#endif

#ifndef HAS_SMOOTH_LAMP_COMMANDS
#error "+ HAS_SMOOTH_LAMP_COMMANDS"
#endif

bool smooth_lamp_limit_off_command(int32_t argc, char* argv[]);
bool smooth_lamp_logistic_shift_command(int32_t argc, char* argv[]);
bool smooth_lamp_mult_command(int32_t argc, char* argv[]);
bool smooth_lamp_diag_command(int32_t argc, char* argv[]);
bool smooth_lamp_init_command(int32_t argc, char* argv[]);
bool smooth_lamp_ctrl_command(int32_t argc, char* argv[]);

#define SMOOTH_LAMP_COMMANDS                                                                                          \
        SHELL_CMD("smooth_lamp_limit_off", "sllf", smooth_lamp_limit_off_command, "SmoothLampLimitOff"),                           \
        SHELL_CMD("smooth_lamp_logistic_shift", "slls", smooth_lamp_logistic_shift_command, "SmoothLampLogShift"),                           \
        SHELL_CMD("smooth_lamp_mult", "slm", smooth_lamp_mult_command, "SmoothLampMult"),                           \
        SHELL_CMD("smooth_lamp_ctrl", "slc", smooth_lamp_ctrl_command, "SmoothLampCtrl"),                           \
        SHELL_CMD("smooth_lamp_diag", "sld", smooth_lamp_diag_command, "SmoothLampDiag"),                           \
        SHELL_CMD("smooth_lamp_init", "sli", smooth_lamp_init_command, "SmoothLampInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* SMOOTH_LAMP_COMMANDS_H */
