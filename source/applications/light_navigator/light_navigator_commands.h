#ifndef LIGHT_NAVIGATOR_COMMANDS_H
#define LIGHT_NAVIGATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool light_navigator_coordinate_command(int32_t argc, char* argv[]);
bool cmd_light_navigator_diag(int32_t argc, char* argv[]);

#define LIGHT_NAVIGATOR_BASE_COMMANDS                                                                            \
    SHELL_CMD("light_navigator_coord", "lnc", light_navigator_coordinate_command, "LightNavigator—oordinate"),   \
    SHELL_CMD("light_navigator_diag", "lnd", cmd_light_navigator_diag, "LightNavigatorDiag"),

#define LIGHT_NAVIGATOR_COMMANDS                                                                       \
    LIGHT_NAVIGATOR_BASE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_NAVIGATOR_COMMANDS_H */
