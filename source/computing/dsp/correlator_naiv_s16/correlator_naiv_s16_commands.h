#ifndef CORRELATOR_NAIV_S16_COMMANDS_H
#define CORRELATOR_NAIV_S16_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ostream.h"
#include "std_includes.h"

#ifndef HAS_CORRELATOR_NAIV_S16_COMMANDS
#error "+HAS_CORRELATOR_NAIV_S16_COMMANDS"
#endif

#ifndef HAS_CORRELATOR_NAIV_S16
#error "+HAS_CORRELATOR_NAIV_S16"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool correlator_naiv_s16_proc_file_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_proc_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_init_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_reset_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_diag_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_calc_frequency_response_command(int32_t argc, char* argv[]);
bool correlator_naiv_s16_graphviz_command(int32_t argc, char* argv[]);

#define CORRELATOR_NAIV_S16_COMMANDS                                                                 \
        SHELL_CMD("correlator_naiv_s16_proc_file", "fipf", correlator_naiv_s16_proc_file_command, "CorrelatorNaivS16ProcFile"),                       \
        SHELL_CMD("correlator_naiv_s16_calc_frequency_response", "ffr", correlator_naiv_s16_calc_frequency_response_command, "CorrelatorNaivS16CalcFrequencyResponse"),                       \
        SHELL_CMD("correlator_naiv_s16_diag", "correlator_naiv_s16d", correlator_naiv_s16_diag_command, "CorrelatorNaivS16Diag"),                       \
        SHELL_CMD("correlator_naiv_s16_graphviz", "correlator_naiv_s16g", correlator_naiv_s16_graphviz_command, "CorrelatorNaivS16Graphviz"),                       \
        SHELL_CMD("correlator_naiv_s16_init", "correlator_naiv_s16i", correlator_naiv_s16_init_command, "CorrelatorNaivS16Init"),                       \
        SHELL_CMD("correlator_naiv_s16_reset", "correlator_naiv_s16r", correlator_naiv_s16_reset_command, "CorrelatorNaivS16Reset"),                       \
        SHELL_CMD("correlator_naiv_s16_proc", "correlator_naiv_s16p", correlator_naiv_s16_proc_command, "CorrelatorNaivS16Proc"),

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_NAIV_S16_COMMANDS_H */
