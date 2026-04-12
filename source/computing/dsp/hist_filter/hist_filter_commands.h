#ifndef HIST_FILTER_COMMANDS_H
#define HIST_FILTER_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_HIST_FILTER
#error "+ HAS_HIST_FILTER"
#endif

#ifndef HAS_HIST_FILTER_COMMANDS
#error "+ HAS_HIST_FILTER_COMMANDS"
#endif

bool hist_filter_diag_command(int32_t argc, char* argv[]);
bool hist_filter_init_command(int32_t argc, char* argv[]);
bool hist_filter_proc_command(int32_t argc, char* argv[]);

#define HIST_FILTER_COMMANDS                                                                                          \
        SHELL_CMD("hist_filter_proc", "hfp", hist_filter_proc_command, "HistFilterProc"),                           \
        SHELL_CMD("hist_filter_diag", "hfd", hist_filter_diag_command, "HistFilterDiag"),                           \
        SHELL_CMD("hist_filter_init", "hfi", hist_filter_init_command, "HistFilterInit"),

#ifdef __cplusplus
}
#endif

#endif /* HIST_FILTER_COMMANDS_H */
