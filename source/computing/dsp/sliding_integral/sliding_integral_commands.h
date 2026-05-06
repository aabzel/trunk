#ifndef SLIDING_INTEGRAL_COMMANDS_H
#define SLIDING_INTEGRAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_SLIDING_INTEGRAL_COMMANDS
#error "+HAS_SLIDING_INTEGRAL_COMMANDS"
#endif

#ifndef HAS_SLIDING_INTEGRAL
#error "+HAS_SLIDING_INTEGRAL"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool sliding_integral_proc_command(int32_t argc, char* argv[]);
bool sliding_integral_init_command(int32_t argc, char* argv[]);
bool sliding_integral_reset_command(int32_t argc, char* argv[]);
bool sliding_integral_diag_command(int32_t argc, char* argv[]);

#define SLIDING_INTEGRAL_COMMANDS                                                                 \
        SHELL_CMD("sliding_integral_diag", "sliding_integrald", sliding_integral_diag_command, "SlidingIntegralDiag"),                       \
        SHELL_CMD("sliding_integral_init", "sliding_integrali", sliding_integral_init_command, "SlidingIntegralInit"),                       \
        SHELL_CMD("sliding_integral_reset", "sliding_integralr", sliding_integral_reset_command, "SlidingIntegralReset"),                       \
        SHELL_CMD("sliding_integral_proc", "sliding_integralp", sliding_integral_proc_command, "SlidingIntegralProc"),

#ifdef __cplusplus
}
#endif

#endif /* SLIDING_INTEGRAL_COMMANDS_H */
