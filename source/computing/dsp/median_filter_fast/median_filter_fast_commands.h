#ifndef MEDIAN_FILTER_FAST_COMMANDS_H
#define MEDIAN_FILTER_FAST_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MEDIAN_FILTER_FAST_COMMANDS
#error "+HAS_MEDIAN_FILTER_FAST_COMMANDS"
#endif /*HAS_MEDIAN_FILTER_FAST_COMMANDS*/

bool median_filter_fast_diag_command(int32_t argc, char* argv[]);
bool median_filter_fast_proc_command(int32_t argc, char* argv[]);

#ifdef HAS_FILE_PC
bool median_filter_fast_calc_frequency_response_command(int32_t argc, char* argv[]);
bool median_filter_fast_calc_frequency_response_norm_command(int32_t argc, char* argv[]);

#define MEDIAN_FILTER_FAST_FILE_COMMANDS                                                                              \
    SHELL_CMD("median_filter_fast_calc_frequency_response", "mfffr", median_filter_fast_calc_frequency_response_command, "MedianFilterFastCalcFrequencyResponse"), \
    SHELL_CMD("median_filter_fast_calc_frequency_response_norm", "mfffrn", median_filter_fast_calc_frequency_response_norm_command, "MedianFilterFastCalcFrequencyResponseNorm"),

#else
#define MEDIAN_FILTER_FAST_FILE_COMMANDS

#endif

#define MEDIAN_FILTER_FAST_COMMANDS       MEDIAN_FILTER_FAST_FILE_COMMANDS                                                                       \
    SHELL_CMD("median_filter_fast_proc", "mffp", median_filter_fast_proc_command, "MedianFilterFastProc"), \
    SHELL_CMD("median_filter_fast_diag", "mffd", median_filter_fast_diag_command, "MEDIAN_FILTER_FASTdiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MEDIAN_FILTER_FAST_COMMANDS_H*/
