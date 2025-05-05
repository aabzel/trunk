#ifndef LIGHT_NAVIGATOR_COMMANDS_H
#define LIGHT_NAVIGATOR_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_light_navigator_diag(int32_t argc, char* argv[]);

#define LIGHT_NAVIGATOR_BASE_COMMANDS                                                                                         \
    SHELL_CMD("light_navigator_diag", "lnd", cmd_light_navigator_diag, "LightNavigatorDiag"),                                             \

#define LIGHT_NAVIGATOR_COMMANDS                                                                                              \
    LIGHT_NAVIGATOR_BASE_COMMANDS                                                                                             \

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_NAVIGATOR_COMMANDS_H */
