#ifndef LOCAL_OSCILLATOR_COMMANDS_H
#define LOCAL_OSCILLATOR_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_LOCAL_OSCILLATOR
#error "+ HAS_LOCAL_OSCILLATOR"
#endif

#ifndef HAS_LOCAL_OSCILLATOR_COMMANDS
#error "+ HAS_LOCAL_OSCILLATOR_COMMANDS"
#endif

bool local_oscillator_calc_command(int32_t argc, char* argv[]);

#define LOCAL_OSCILLATOR_COMMANDS                                                                        \
        SHELL_CMD("local_oscillator_calc", "loc", local_oscillator_calc_command, "LocalOscillatorCalc"),

#ifdef __cplusplus
}
#endif

#endif /* LOCAL_OSCILLATOR_COMMANDS_H */
