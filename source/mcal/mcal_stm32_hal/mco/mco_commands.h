#ifndef MCO_COMMANDS_H
#define MCO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_MCO
#error "+HAS_MCO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool mco_config_command(int32_t argc, char* argv[]);

#define MCO_COMMANDS                                                         \
    SHELL_CMD("mco_config", "mc", mco_config_command, "McoConfig"),

#ifdef __cplusplus
}
#endif

#endif /* MCO_COMMANDS_H */
