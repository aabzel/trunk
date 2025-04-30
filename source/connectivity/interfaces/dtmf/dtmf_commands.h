#ifndef DTMF_COMMANDS_H
#define DTMF_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool dtmf_calc_period_command(int32_t argc, char* argv[]);
bool dtmf_diag_command(int32_t argc, char* argv[]);
bool dtmf_send_command(int32_t argc, char* argv[]);
bool dtmf_send_char_command(int32_t argc, char* argv[]);

#define DTMF_COMMANDS                                                         \
    SHELL_CMD("dtmf_calc_period", "dtp", dtmf_calc_period_command, "DtmfCalcPeriod"),   \
    SHELL_CMD("dtmf_char", "dtc", dtmf_send_char_command, "DtmfSendChar"),   \
    SHELL_CMD("dtmf_diag", "dtd", dtmf_diag_command, "DtmfDiag"),            \
    SHELL_CMD("dtmf_send", "dts", dtmf_send_command, "DtmfSend"),

#ifdef __cplusplus
}
#endif

#endif /* DTMF_COMMANDS_H */
