#ifndef END_OF_BLOCK_COMMANDS_H
#define END_OF_BLOCK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool end_of_block_check_command(int32_t argc, char* argv[]);

#define END_OF_BLOCK_COMMANDS                                                              \
    SHELL_CMD("end_of_block_check", "eob", end_of_block_check_command, "EndOfBlockCheck"),


#ifdef __cplusplus
}
#endif

#endif /* END_OF_BLOCK_COMMANDS_H */
