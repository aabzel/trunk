#ifndef SCHMITT_TRIGGER_COMMANDS_H
#define SCHMITT_TRIGGER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_SCHMITT_TRIGGER
#error "+HAS_SCHMITT_TRIGGER"
#endif  /*HAS_SCHMITT_TRIGGER*/

#ifndef HAS_SCHMITT_TRIGGER_COMMANDS
#error "+HAS_SCHMITT_TRIGGER_COMMANDS"
#endif  /*HAS_SCHMITT_TRIGGER_COMMANDS*/

bool schmitt_trigger_proc_command(int32_t argc, char* argv[]);
bool schmitt_trigger_set_command(int32_t argc, char* argv[]);
bool schmitt_trigger_diag_command(int32_t argc, char* argv[]);

#define SCHMITT_TRIGGER_COMMANDS                                                                        \
    SHELL_CMD("schmitt_trigger_set", "scts", schmitt_trigger_set_command, "SchmittTriggerSet"),          \
    SHELL_CMD("schmitt_trigger_diag", "sctd", schmitt_trigger_diag_command, "SchmittTriggerDiag"),       \
    SHELL_CMD("schmitt_trigger_proc", "sctp", schmitt_trigger_proc_command, "SchmittTriggerProc"),

#ifdef __cplusplus
}
#endif

#endif /* SCHMITT_TRIGGER_COMMANDS_H */
