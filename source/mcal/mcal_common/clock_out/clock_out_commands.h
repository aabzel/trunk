#ifndef CLOCK_OUT_COMMANDS_H
#define CLOCK_OUT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifdef HAS_CLOCK_OUT_CUSTOM_COMMANDS
#include "clock_out_custom_commands.h"
#else
#define CLOCK_OUT_CUSTOM_COMMANDS
#endif

#ifndef HAS_CLOCK_OUT
#error "+HAS_CLOCK_OUT"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool clock_out_init_command(int32_t argc, char* argv[]);
bool clock_out_diag_command(int32_t argc, char* argv[]);
bool clock_out_ctrl_command(int32_t argc, char* argv[]);

#define CLOCK_OUT_COMMANDS   CLOCK_OUT_CUSTOM_COMMANDS                                                      \
    SHELL_CMD("clock_out_init", "coi", clock_out_init_command, "ClockOutInit"),   \
    SHELL_CMD("clock_out_diag", "cod", clock_out_diag_command, "ClockOutDiag"),   \
    SHELL_CMD("clock_out_ctrl", "coc", clock_out_ctrl_command, "ClockOutCtrl"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_OUT_COMMANDS_H */
