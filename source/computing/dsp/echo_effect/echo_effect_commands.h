#ifndef ECHO_EFFECT_COMMANDS_H
#define ECHO_EFFECT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


bool echo_effect_diag_command(int32_t argc, char* argv[]);
bool echo_effect_factor_command(int32_t argc, char* argv[]);

#define ECHO_EFFECT_COMMANDS                                                                \
    SHELL_CMD("echo_effect_factor", "eef", echo_effect_factor_command, "EchoEffectFactor"), \
    SHELL_CMD("echo_effect_diag", "eed", echo_effect_diag_command, "EchoEffectDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*ECHO_EFFECT_COMMANDS_H*/
