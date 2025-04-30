
#ifndef STATISTICS_COMMANDS_H
#define STATISTICS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool statistics_bar_chart_command(int32_t argc, char* argv[]);
bool statistics_calc_command(int32_t argc, char* argv[]);
bool statistics_diag_command(int32_t argc, char* argv[]);
bool statistics_load_command(int32_t argc, char* argv[]);

#define STATISTICS_COMMANDS                                                                        \
    SHELL_CMD("statistics_bar_chart", "stb", statistics_bar_chart_command, "StatisticsBarChart"),  \
    SHELL_CMD("statistics_calc", "stc", statistics_calc_command, "StatisticsCalc"),     \
    SHELL_CMD("statistics_load", "stl", statistics_load_command, "StatisticsLoad"),     \
    SHELL_CMD("statistics_diag", "std", statistics_diag_command, "StatisticsDiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*STATISTICS_COMMANDS_H*/
