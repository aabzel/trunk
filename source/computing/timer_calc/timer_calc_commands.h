#ifndef TIMER_CALC_COMMANDS_H
#define TIMER_CALC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#define "+HAS_DIAG"
#endif

bool timer_calc_artery_command(int32_t argc, char* argv[]);

#define TIMER_CALC_COMMANDS                                                            \
    SHELL_CMD("timer_calc_artery", "tca", timer_calc_artery_command, "TimerCalcArtery"),

#ifdef __cplusplus
}
#endif

#endif /* TIMER_CALC_COMMANDS_H  */
