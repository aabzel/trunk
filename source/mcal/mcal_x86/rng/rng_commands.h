#ifndef TRNG_COMMANDS_H
#define TRNG_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool trng_read_command(int32_t argc, char* argv[]);

#define TRNG_COMMANDS SHELL_CMD("rng_read", "rng", trng_read_command, "Rand num get"),

#ifdef __cplusplus
}
#endif

#endif /* TRNG_COMMANDS_H */
