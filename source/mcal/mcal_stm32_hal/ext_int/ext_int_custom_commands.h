#ifndef EXT_INT_CUSTOM_COMMANDS_H
#define EXT_INT_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif

#ifndef HAS_EXT_INT_COMMANDS
#error "+HAS_EXT_INT_COMMANDS"
#endif

#include "std_includes.h"

bool ext_int_test_isr_command(int32_t argc, char* argv[]) ;

#define EXT_INT_CUSTOM_COMMANDS  \
    SHELL_CMD("ext_int_test", "eiti", ext_int_test_isr_command, "ExtIntTestIsr"),

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_CUSTOM_COMMANDS_H */
