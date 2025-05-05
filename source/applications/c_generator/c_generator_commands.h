#ifndef C_GENERATOR_COMMANDS_H
#define C_GENERATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool c_generator_diag_command(int32_t argc, char* argv[]);
bool c_generator_proc_command(int32_t argc, char* argv[]);
bool c_generator_function_cap_command(int32_t argc, char* argv[]);

#define C_GENERATOR_COMMANDS                                                                       \
    SHELL_CMD("c_generator_fun_cap", "cgf", c_generator_function_cap_command, "cGeneratorFunCap"), \
    SHELL_CMD("c_generator_diag", "cgd", c_generator_diag_command, "cGeneratorDiag"),              \
    SHELL_CMD("c_generator_proc", "cgr", c_generator_proc_command, "cGeneratorProc"),

#ifdef __cplusplus
}
#endif

#endif /* C_GENERATOR_COMMANDS_H */
