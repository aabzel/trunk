#ifndef CAN_DIFF_COMMANDS_H
#define CAN_DIFF_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CAN_DIFF
#error "+ HAS_CAN_DIFF"
#endif

#ifndef HAS_CAN_DIFF_COMMANDS
#error "+ HAS_CAN_DIFF_COMMANDS"
#endif

bool can_diff_diag_command(int32_t argc, char* argv[]);
bool can_diff_init_command(int32_t argc, char* argv[]);
bool can_diff_watch_command(int32_t argc, char* argv[]);

#define CAN_DIFF_COMMANDS                                                                                    \
        SHELL_CMD("can_diff_watch", "cdw", can_diff_watch_command, "CanDiffSetWatch"),                           \
        SHELL_CMD("can_diff_diag", "cdd", can_diff_diag_command, "CanDiffDiag"),                           \
        SHELL_CMD("can_diff_init", "cdi", can_diff_init_command, "CanDiffInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* CAN_DIFF_COMMANDS_H */
