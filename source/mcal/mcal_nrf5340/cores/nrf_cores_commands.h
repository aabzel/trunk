#ifndef NRF_CORES_COMMANDS_H
#define NRF_CORES_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_NRF_CORES_COMMANDS
#error "+HAS_NRF_CORES_COMMANDS"
#endif

#ifndef HAS_NRF_CORES
#error "+HAS_NRF_CORES"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool nrf_core_set_command(int32_t argc, char* argv[]);

#define NRF_CORES_SPECIFIC_COMMANDS                                                                          \
        SHELL_CMD("nrf_core_set", "ngs", nrf_core_set_command, "NrfGpioSet"),

#ifdef __cplusplus
}
#endif

#endif /* NRF_CORES_COMMANDS_H */
