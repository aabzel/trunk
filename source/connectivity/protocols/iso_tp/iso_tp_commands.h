#ifndef ISO_TP_COMMAND_H
#define ISO_TP_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cli_drv.h"

bool iso_tp_writer_command(int32_t argc, char* argv[]);
bool iso_tp_diag_command(int32_t argc, char* argv[]);
bool iso_tp_init_command(int32_t argc, char* argv[]);
bool iso_tp_send_command(int32_t argc, char* argv[]);
bool iso_tp_test_send_jumbo_command(int32_t argc, char* argv[]);
bool iso_tp_buff_command(int32_t argc, char* argv[]);
bool iso_tp_compose_address_command(int32_t argc, char* argv[]);

#define ISO_TP_COMMANDS                                                                       \
        SHELL_CMD("iso_tp_writer", "tpw", iso_tp_writer_command, "IsoTpWriter"),             \
        SHELL_CMD("iso_tp_buff", "tpb", iso_tp_buff_command, "IsoTpBuff"),                    \
        SHELL_CMD("iso_tp_init", "tpi", iso_tp_init_command, "IsoTpInit"),                    \
        SHELL_CMD("iso_tp_diag", "tpd", iso_tp_diag_command, "IsoTpDiag"),                    \
        SHELL_CMD("iso_tp_compose_addr", "tpca", iso_tp_compose_address_command, "IsoTpComposeAddress"),                \
        SHELL_CMD("iso_tp_test_send_jumbo", "tptsj", iso_tp_test_send_jumbo_command, "IsoTpTestSendJumbo"),             \
        SHELL_CMD("iso_tp_send", "iso_tp", iso_tp_send_command, "IsoTpSend"),

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_COMMAND_H */
