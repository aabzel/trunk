#ifndef JUMPER_CODE_COMMANDS_H
#define JUMPER_CODE_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_JUMPER_CODE
#error "+ HAS_JUMPER_CODE"
#endif

#ifndef HAS_JUMPER_CODE_COMMANDS
#error "+ HAS_JUMPER_CODE_COMMANDS"
#endif

bool jumper_code_diag_command(int32_t argc, char* argv[]);
bool jumper_code_init_command(int32_t argc, char* argv[]);

#define JUMPER_CODE_COMMANDS                                                                                        \
        SHELL_CMD("jumper_code_diag", "jcd", jumper_code_diag_command, "JumperCodeDiag"),                           \
        SHELL_CMD("jumper_code_init", "jci", jumper_code_init_command, "JumperCodeInit"),

#ifdef __cplusplus
}
#endif

#endif /* JUMPER_CODE_COMMANDS_H */
