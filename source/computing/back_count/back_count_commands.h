#ifndef BACK_COUNT_COMMANDS_H
#define BACK_COUNT_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_BACK_COUNT
#error "+ HAS_BACK_COUNT"
#endif

#ifndef HAS_BACK_COUNT_COMMANDS
#error "+ HAS_BACK_COUNT_COMMANDS"
#endif

bool back_count_diag_command(int32_t argc, char* argv[]);
bool back_count_init_command(int32_t argc, char* argv[]);

#define BACK_COUNT_COMMANDS                                                                                          \
        SHELL_CMD("back_count_diag", "swd", back_count_diag_command, "BackCountDiag"),                           \
        SHELL_CMD("back_count_init", "swi", back_count_init_command, "BackCountInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* BACK_COUNT_COMMANDS_H */
