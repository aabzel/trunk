#ifndef IIR_COMMANDS_H
#define IIR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_IIR_COMMANDS
#error "+HAS_IIR_COMMANDS"
#endif /*HAS_IIR_COMMANDS*/

bool iir_lowpas_1st_order_command(int32_t argc, char* argv[]);
bool iir_lowpas_1st_order_v2_command(int32_t argc, char* argv[]);
bool iir_diag_command(int32_t argc, char* argv[]);
bool iir_proc_command(int32_t argc, char* argv[]);
bool iir_calc_frequency_response_command(int32_t argc, char* argv[]);
bool iir_calc_frequency_response_norm_command(int32_t argc, char* argv[]);

#define IIR_COMMANDS                                                                              \
    SHELL_CMD("iir_lowpas_1st_order_v2", "iilp2", iir_lowpas_1st_order_v2_command, "IirLowPasFilter1stOrderV2"),   \
    SHELL_CMD("iir_lowpas_1st_order", "iilp", iir_lowpas_1st_order_command, "IirLowPasFilter1stOrder"),   \
    SHELL_CMD("iir_calc_frequency_response", "iifr", iir_calc_frequency_response_command, "IirCalcFrequencyResponse"), \
    SHELL_CMD("iir_calc_frequency_response_norm", "iifrn", iir_calc_frequency_response_norm_command, "IirCalcFrequencyResponseNorm"), \
    SHELL_CMD("iir_proc", "iip", iir_proc_command, "IirProc"), \
    SHELL_CMD("iir_diag", "iid", iir_diag_command, "IIRdiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*IIR_COMMANDS_H*/
