#ifndef RADIO_COMMANDS_H
#define RADIO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool radio_diag_command(int32_t argc, char* argv[]);


#define RADIO_COMMANDS_BASE \
    SHELL_CMD("radio_diag", "ld", radio_diag_command, "RadioDiag"),


#ifdef HAS_DEBUG
bool radio_horizon_command(int32_t argc, char* argv[]);

#define RADIO_COMMANDS_DEBUG \
    SHELL_CMD("radio_mast", "lh", radio_horizon_command, "mast horizon"),
#else
#define RADIO_COMMANDS_DEBUG
#endif

#define RADIO_COMMANDS \
        RADIO_COMMANDS_BASE \
        RADIO_COMMANDS_DEBUG


#ifdef __cplusplus
}
#endif

#endif /* RADIO_COMMANDS_H */
