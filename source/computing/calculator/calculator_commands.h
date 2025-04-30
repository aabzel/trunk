#ifndef CALCULATOR_COMMANDS_H
#define CALCULATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool calculator_calc_command(int32_t argc, char* argv[]);

#define CALCULATOR_COMMANDS                                               \
    SHELL_CMD("calculator", "calc", calculator_calc_command, "Calc"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*CALCULATOR_COMMANDS_H*/
