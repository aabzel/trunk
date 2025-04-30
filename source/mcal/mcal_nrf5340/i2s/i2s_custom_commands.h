#ifndef I2S_NRF_COMMANDS_H
#define I2S_NRF_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool i2s_nrf_diag_command(int32_t argc, char* argv[]);
bool i2s_nrf_echo_command(int32_t argc, char* argv[]);

#define I2S_CUSTOM_COMMANDS                                              \
               SHELL_CMD("i2s_nrf_echo", "i2sne", i2s_nrf_echo_command, "I2sNrfEcho"),         \
               SHELL_CMD("i2s_nrf_diag", "i2snd", i2s_nrf_diag_command, "I2sNrfDiag"),

#ifdef __cplusplus
}
#endif

#endif /* I2S_NRF_COMMANDS_H */
