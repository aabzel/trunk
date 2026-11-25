#ifndef CAN_CAT_COMMANDS_H
#define CAN_CAT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CAN_CAT
#error "+ HAS_CAN_CAT"
#endif

#ifndef HAS_CAN_CAT_COMMANDS
#error "+ HAS_CAN_CAT_COMMANDS"
#endif

bool can_cat_config_command(int32_t argc, char* argv[]);
bool can_cat_diag_command(int32_t argc, char* argv[]);
bool can_cat_init_command(int32_t argc, char* argv[]);

#define CAN_CAT_COMMANDS                                                                                      \
        SHELL_CMD("can_cat_diag", "ccd", can_cat_diag_command, "CanCatDiag"),                                 \
        SHELL_CMD("can_cat_config", "ccc", can_cat_config_command, "CanCatConfig"),                           \
        SHELL_CMD("can_cat_init", "cci", can_cat_init_command, "CanCatInit"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_CAT_COMMANDS_H */
