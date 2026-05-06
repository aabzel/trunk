#ifndef DC_CUT_FILTER_COMMANDS_H
#define DC_CUT_FILTER_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DC_CUT_FILTER
#error "+ HAS_DC_CUT_FILTER"
#endif

#ifndef HAS_DC_CUT_FILTER_COMMANDS
#error "+ HAS_DC_CUT_FILTER_COMMANDS"
#endif

bool dc_cut_filter_diag_command(int32_t argc, char* argv[]);
bool dc_cut_filter_init_command(int32_t argc, char* argv[]);

#define DC_CUT_FILTER_COMMANDS                                                                                          \
        SHELL_CMD("dc_cut_filter_diag", "dcfd", dc_cut_filter_diag_command, "DcCutFilterDiag"),                           \
        SHELL_CMD("dc_cut_filter_init", "dcfi", dc_cut_filter_init_command, "DcCutFilterInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* DC_CUT_FILTER_COMMANDS_H */
