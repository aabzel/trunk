#ifndef MEDIAN_FILTER_COMMANDS_H
#define MEDIAN_FILTER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MEDIAN_FILTER_COMMANDS
#error "+HAS_MEDIAN_FILTER_COMMANDS"
#endif

bool median_filter_diag_command(int32_t argc, char* argv[]);
bool median_filter_proc_command(int32_t argc, char* argv[]);

#ifdef HAS_FILE_PC
bool median_filter_calc_frequency_response_command(int32_t argc, char* argv[]);
bool median_filter_calc_frequency_response_norm_command(int32_t argc, char* argv[]);

#define MEDIAN_FILTER_FILE_COMMANDS                                                                              \
    SHELL_CMD("median_filter_calc_frequency_response", "mffr", median_filter_calc_frequency_response_command, "MedianFilterCalcFrequencyResponse"), \
    SHELL_CMD("median_filter_calc_frequency_response_norm", "mffrn", median_filter_calc_frequency_response_norm_command, "MedianFilterCalcFrequencyResponseNorm"),

#else
#define MEDIAN_FILTER_FILE_COMMANDS

#endif

#define MEDIAN_FILTER_COMMANDS       MEDIAN_FILTER_FILE_COMMANDS                                                                       \
    SHELL_CMD("median_filter_proc", "mfp", median_filter_proc_command, "MedianFilterProc"), \
    SHELL_CMD("median_filter_diag", "mfd", median_filter_diag_command, "MEDIAN_FILTERdiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MEDIAN_FILTER_COMMANDS_H*/
