#ifndef TRNG_COMMANDS_H
#define TRNG_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_TRNG_CUSTOM_COMMANDS
#include "trng_custom_commands.h"
#else
#define TRNG_CUSTOM_COMMANDS
#endif


#ifndef HAS_TRNG
#error "+ HAS_TRNG"
#endif

#ifndef HAS_TRNG_COMMANDS
#error "+ HAS_TRNG_COMMANDS"
#endif

bool trng_diag_command(int32_t argc, char* argv[]);
bool trng_init_command(int32_t argc, char* argv[]);

#define TRNG_COMMANDS                                                                                          \
        TRNG_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("trng_diag", "trngd", trng_diag_command, "tRngDiag"),                           \
        SHELL_CMD("trng_init", "trng", trng_init_command, "tRngInit"),

#ifdef __cplusplus
}
#endif

#endif /* TRNG_COMMANDS_H */
