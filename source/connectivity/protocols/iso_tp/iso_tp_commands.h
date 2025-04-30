#ifndef ISO_TP_COMMAND_H
#define ISO_TP_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool iso_tp_diag_command(int32_t argc, char* argv[]);
bool iso_tp_send_command(int32_t argc, char* argv[]);
bool iso_tp_buff_command(int32_t argc, char* argv[]);

#define ISO_TP_COMMANDS                                                                                                  \
        SHELL_CMD("iso_tp_diag", "tpd", iso_tp_diag_command, "IsoTpDiag"),                                                 \
        SHELL_CMD("iso_tp_buff", "tpb", iso_tp_buff_command, "IsoTpBuff"),                                                 \
        SHELL_CMD("iso_tp_send", "iso_tp", iso_tp_send_command, "IsoTpSend"),

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_COMMAND_H */
