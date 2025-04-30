#ifndef DECIMATOR_COMMANDS_H
#define DECIMATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <std_includes.h>

#include "ostream.h"

#ifndef HAS_DECIMATOR
#error "+HAS_DECIMATOR"
#endif  /*HAS_DECIMATOR*/

#ifndef HAS_DECIMATOR_COMMANDS
#error "+HAS_DECIMATOR_COMMANDS"
#endif  /*HAS_DECIMATOR_COMMANDS*/

bool decimator_proc_command(int32_t argc, char* argv[]);
bool decimator_diag_command(int32_t argc, char* argv[]);

#define DECIMATOR_COMMANDS                                                                        \
    SHELL_CMD("decimator_diag", "ded", decimator_diag_command, "DecimatorDiag"),       \
    SHELL_CMD("decimator_proc", "dep", decimator_proc_command, "DecimatorProc"),

#ifdef __cplusplus
}
#endif

#endif /* DECIMATOR_COMMANDS_H */
