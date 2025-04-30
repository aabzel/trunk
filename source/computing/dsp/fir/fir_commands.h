#ifndef FIR_COMMANDS_H
#define FIR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_FIR_COMMANDS
#error "+HAS_FIR_COMMANDS"
#endif

#ifndef HAS_FIR
#error "+HAS_FIR"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool fir_impulse_response_command(int32_t argc, char* argv[]);
bool fir_proc_file_command(int32_t argc, char* argv[]);
bool fir_proc_command(int32_t argc, char* argv[]);
bool fir_synthesize_command(int32_t argc, char* argv[]);
bool fir_init_command(int32_t argc, char* argv[]);
bool fir_reset_command(int32_t argc, char* argv[]);
bool fir_diag_command(int32_t argc, char* argv[]);
bool fir_calc_frequency_response_command(int32_t argc, char* argv[]);
bool fir_graphviz_command(int32_t argc, char* argv[]);

#define FIR_COMMANDS                                                                 \
        SHELL_CMD("fir_proc_file", "fipf", fir_proc_file_command, "FirProcFile"),                       \
        SHELL_CMD("fir_impulse_response", "fii", fir_impulse_response_command, "FirCalcImpulseResponse"),                       \
        SHELL_CMD("fir_calc_frequency_response", "ffr", fir_calc_frequency_response_command, "FirCalcFrequencyResponse"),                       \
        SHELL_CMD("fir_synthesize", "fis", fir_synthesize_command, "FirSynthesize"),                       \
        SHELL_CMD("fir_diag", "fird", fir_diag_command, "FirDiag"),                       \
        SHELL_CMD("fir_graphviz", "firg", fir_graphviz_command, "FirGraphviz"),                       \
        SHELL_CMD("fir_init", "firi", fir_init_command, "FirInit"),                       \
        SHELL_CMD("fir_reset", "firr", fir_reset_command, "FirReset"),                       \
        SHELL_CMD("fir_proc", "firp", fir_proc_command, "FirProc"),

#ifdef __cplusplus
}
#endif

#endif /* FIR_COMMANDS_H */
