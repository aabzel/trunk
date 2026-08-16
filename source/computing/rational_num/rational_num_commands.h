#ifndef RATIONAL_NUM_COMMANDS_H
#define RATIONAL_NUM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_RATIONAL_NUM
#error "+ HAS_RATIONAL_NUM"
#endif

#ifndef HAS_RATIONAL_NUM_COMMANDS
#error "+ HAS_RATIONAL_NUM_COMMANDS"
#endif

bool float_to_rational_number_command(int32_t argc, char* argv[]);

#define RATIONAL_NUM_COMMANDS                                                                \
    SHELL_CMD("float_to_rational_number", "frn", float_to_rational_number_command, "FloatToRationalNumber"),




#ifdef __cplusplus
}
#endif

#endif /* RATIONAL_NUM_COMMANDS_H */
