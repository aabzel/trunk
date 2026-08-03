#ifndef CORRELATOR_S16_COMMANDS_H
#define CORRELATOR_S16_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ostream.h"
#include "std_includes.h"

#ifndef HAS_CORRELATOR_S16_COMMANDS
#error "+HAS_CORRELATOR_S16_COMMANDS"
#endif

#ifndef HAS_CORRELATOR_S16
#error "+HAS_CORRELATOR_S16"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool correlator_s16_impulse_response_command(int32_t argc, char* argv[]);
bool correlator_s16_proc_file_command(int32_t argc, char* argv[]);
bool correlator_s16_proc_command(int32_t argc, char* argv[]);
bool correlator_s16_init_command(int32_t argc, char* argv[]);
bool correlator_s16_reset_command(int32_t argc, char* argv[]);
bool correlator_s16_diag_command(int32_t argc, char* argv[]);
bool correlator_s16_calc_frequency_response_command(int32_t argc, char* argv[]);
bool correlator_s16_graphviz_command(int32_t argc, char* argv[]);

#define CORRELATOR_S16_COMMANDS                                                                 \
        SHELL_CMD("correlator_s16_proc_file", "fipf", correlator_s16_proc_file_command, "CorrelatorS16ProcFile"),                       \
        SHELL_CMD("correlator_s16_impulse_response", "fii", correlator_s16_impulse_response_command, "CorrelatorS16CalcImpulseResponse"),                       \
        SHELL_CMD("correlator_s16_calc_frequency_response", "ffr", correlator_s16_calc_frequency_response_command, "CorrelatorS16CalcFrequencyResponse"),                       \
        SHELL_CMD("correlator_s16_diag", "correlator_s16d", correlator_s16_diag_command, "CorrelatorS16Diag"),                       \
        SHELL_CMD("correlator_s16_graphviz", "correlator_s16g", correlator_s16_graphviz_command, "CorrelatorS16Graphviz"),                       \
        SHELL_CMD("correlator_s16_init", "correlator_s16i", correlator_s16_init_command, "CorrelatorS16Init"),                       \
        SHELL_CMD("correlator_s16_reset", "correlator_s16r", correlator_s16_reset_command, "CorrelatorS16Reset"),                       \
        SHELL_CMD("correlator_s16_proc", "correlator_s16p", correlator_s16_proc_command, "CorrelatorS16Proc"),

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_S16_COMMANDS_H */
