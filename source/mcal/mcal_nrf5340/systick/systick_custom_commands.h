#ifndef NRF53_SYSTICK_COMMANDS_H
#define NRF53_SYSTICK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

#ifndef HAS_SYSTICK_CUSTOM_COMMANDS
#error "+HAS_SYSTICK_CUSTOM_COMMANDS"
#endif

bool systick_nrf53_diag_command(int32_t argc, char* argv[]);
bool systick_set_period_command(int32_t argc, char* argv[]);

#define SYSTICK_CUSTOM_COMMANDS                                                                     \
        SHELL_CMD("systic_set_per", "stksp", systick_set_period_command, "SysTicSetPeriod"),       \
        SHELL_CMD("systic_stm_diag", "stksd", systick_nrf53_diag_command, "SysTicStmDiag"),

#ifdef __cplusplus
}
#endif

#endif /* NRF53_SYSTICK_COMMANDS_H */
