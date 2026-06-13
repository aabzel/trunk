#ifndef BICYCLE_HEADLAMP_COMMANDS_H
#define BICYCLE_HEADLAMP_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_BICYCLE_HEADLAMP
#error "+ HAS_BICYCLE_HEADLAMP"
#endif

#ifndef HAS_BICYCLE_HEADLAMP_COMMANDS
#error "+ HAS_BICYCLE_HEADLAMP_COMMANDS"
#endif

bool bicycle_headlamp_diag_command(int32_t argc, char* argv[]);
bool bicycle_headlamp_init_command(int32_t argc, char* argv[]);

#define BICYCLE_HEADLAMP_COMMANDS                                                                                   \
        SHELL_CMD("bicycle_headlamp_diag", "bhld", bicycle_headlamp_diag_command, "BicycleHeadLampDiag"),           \
        SHELL_CMD("bicycle_headlamp_init", "bhli", bicycle_headlamp_init_command, "BicycleHeadLampInit"),

#ifdef __cplusplus
}
#endif

#endif /* BICYCLE_HEADLAMP_COMMANDS_H */
