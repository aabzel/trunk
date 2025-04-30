#ifndef NVS_ZEPHYR_COMMANDS_H
#define NVS_ZEPHYR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

#define NVS_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* NVS_COMMANDS_H */
