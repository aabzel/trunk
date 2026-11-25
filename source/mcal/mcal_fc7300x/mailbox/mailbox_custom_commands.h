#ifndef MAILBOX_CUSTOM_COMMANDS_H
#define MAILBOX_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MAILBOX
#error "+HAS_MAILBOX"
#endif /*HAS_MAILBOX*/

#ifndef HAS_MAILBOX_COMMANDS
#error "+HAS_MAILBOX_COMMANDS"
#endif /*HAS_MAILBOX_COMMANDS*/

bool mailbox_diag_low_level_command(int32_t argc, char* argv[]);
bool mailbox_raw_reg_command(int32_t argc, char* argv[]);
bool mailbox_diag_channel_command(int32_t argc, char* argv[]);
bool mailbox_diag_channel_2_command(int32_t argc, char* argv[]);

#define MAILBOX_CUSTOM_COMMANDS                                                                              \
    SHELL_CMD("mailbox_raw_reg", "mbrr", mailbox_raw_reg_command, "MailBoxRawReg"),                          \
    SHELL_CMD("mailbox_diag_channel", "mbdc", mailbox_diag_channel_command, "MailBoxDiagChannel"),           \
    SHELL_CMD("mailbox_diag_channel2", "mbdc2", mailbox_diag_channel_2_command, "MailBoxDiagChannel2"),           \
    SHELL_CMD("mailbox_diag_low_level", "mbdl", mailbox_diag_low_level_command, "MailBoxDiagLowLevel"),


#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_CUSTOM_COMMANDS_H */
