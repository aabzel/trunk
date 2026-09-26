#ifndef PROBING_PULSE_COMMANDS_H
#define PROBING_PULSE_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_PROBING_PULSE
#error "+ HAS_PROBING_PULSE"
#endif

#ifndef HAS_PROBING_PULSE_COMMANDS
#error "+ HAS_PROBING_PULSE_COMMANDS"
#endif

bool probing_pulse_diag_command(int32_t argc, char* argv[]);
bool probing_pulse_init_command(int32_t argc, char* argv[]);

#define PROBING_PULSE_COMMANDS                                                                                         \
        SHELL_CMD("probing_pulse_diag", "swd", probing_pulse_diag_command, "ProbingPulseDiag"),                        \
        SHELL_CMD("probing_pulse_init", "swi", probing_pulse_init_command, "ProbingPulseInit"),

#ifdef __cplusplus
}
#endif

#endif /* PROBING_PULSE_COMMANDS_H */
