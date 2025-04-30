#ifndef UDS_COMMAND_H
#define UDS_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool uds_diag_command(int32_t argc, char* argv[]);
bool uds_start_routine_command(int32_t argc, char* argv[]);
bool uds_send_command(int32_t argc, char* argv[]);
bool uds_read_data_by_identifier_command(int32_t argc, char* argv[]);
bool uds_did_diag_command(int32_t argc, char* argv[]);

#define UDS_COMMANDS                                                                             \
        SHELL_CMD("uds_did_diag", "udid", uds_did_diag_command, "UdsDidDiag"), \
        SHELL_CMD("uds_read_id", "udi", uds_read_data_by_identifier_command, "UdsReadDataById"), \
        SHELL_CMD("uds_diag", "udd", uds_diag_command, "UdsDiag"),                               \
        SHELL_CMD("uds_start_routine", "usr", uds_start_routine_command, "UdsStartRoutine"),     \
        SHELL_CMD("uds_send", "uds", uds_send_command, "UdsSend"),

#ifdef __cplusplus
}
#endif

#endif /* UDS_COMMAND_H */
