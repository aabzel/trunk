#ifndef CLOCK_ZEPHYR_COMMANDS_H
#define CLOCK_ZEPHYR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_ZEPHYR_COMMANDS_H */
