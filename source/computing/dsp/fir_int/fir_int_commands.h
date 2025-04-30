#ifndef FIR_INT_COMMANDS_H
#define FIR_INT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "ostream.h"

#ifndef HAS_FIR_INT_COMMANDS
#error "+HAS_FIR_INT_COMMANDS"
#endif

#ifndef HAS_FIR_INT
#error "+HAS_FIR_INT"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool fir_int_impulse_response_command(int32_t argc, char* argv[]);
bool fir_int_proc_command(int32_t argc, char* argv[]);
bool fir_int_synthesize_command(int32_t argc, char* argv[]);
bool fir_int_init_command(int32_t argc, char* argv[]);
bool fir_int_reset_command(int32_t argc, char* argv[]);
bool fir_int_diag_command(int32_t argc, char* argv[]);
bool fir_int_calc_frequency_response_command(int32_t argc, char* argv[]);
bool fir_int_graphviz_command(int32_t argc, char* argv[]);

#define FIR_INT_COMMANDS                                                                 \
        SHELL_CMD("fir_int_impulse_response", "ftii", fir_int_impulse_response_command, "FirIntCalcImpulseResponse"),                       \
        SHELL_CMD("fir_int_calc_frequency_response", "ftfr", fir_int_calc_frequency_response_command, "FirIntCalcFrequencyResponse"),                       \
        SHELL_CMD("fir_int_synthesize", "ftis", fir_int_synthesize_command, "FirIntSynthesize"),                       \
        SHELL_CMD("fir_int_diag", "fird", fir_int_diag_command, "FirIntDiag"),                       \
        SHELL_CMD("fir_int_graphviz", "ftirg", fir_int_graphviz_command, "FirIntGraphviz"),                       \
        SHELL_CMD("fir_int_init", "ftiri", fir_int_init_command, "FirIntInit"),                       \
        SHELL_CMD("fir_int_reset", "ftirr", fir_int_reset_command, "FirIntReset"),                       \
        SHELL_CMD("fir_int_proc", "ftirp", fir_int_proc_command, "FirIntProc"),

#ifdef __cplusplus
}
#endif

#endif /* FIR_INT_COMMANDS_H */
