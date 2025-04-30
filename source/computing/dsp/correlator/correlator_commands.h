#ifndef CORRELATOR_COMMANDS_H
#define CORRELATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


bool correlator_diag_command(int32_t argc, char* argv[]);

#define CORRELATOR_COMMANDS                                                                \
    SHELL_CMD("correlator_diag", "cod", correlator_diag_command, "CorrelatorDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*CORRELATOR_COMMANDS_H*/
