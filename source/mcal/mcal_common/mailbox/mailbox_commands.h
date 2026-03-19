#ifndef MAILBOX_COMMANDS_H
#define MAILBOX_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#ifdef HAS_MAILBOX_CUSTOM_COMMANDS
#include "mailbox_custom_commands.h"
#else
#define MAILBOX_CUSTOM_COMMANDS
#endif

#ifndef HAS_MAILBOX
#error "+HAS_MAILBOX"
#endif /*HAS_MAILBOX*/

#ifndef HAS_MAILBOX_COMMANDS
#error "+HAS_MAILBOX_COMMANDS"
#endif

bool mailbox_init_command(int32_t argc, char* argv[]);
bool mailbox_diag_command(int32_t argc, char* argv[]);
bool mailbox_send_low_level_command(int32_t argc, char* argv[]);
bool mailbox_send_command(int32_t argc, char* argv[]);

#define MAILBOX_COMMANDS                                                       \
    MAILBOX_CUSTOM_COMMANDS                                                    \
    SHELL_CMD("mailbox_send", "mbs", mailbox_send_command, "MailBoxSend"),     \
    SHELL_CMD("mailbox_init", "mbi", mailbox_init_command, "MailBoxInit"),     \
    SHELL_CMD("mailbox_send_low_level", "mbsl", mailbox_send_low_level_command, "MailBoxSendLowLevel"),     \
    SHELL_CMD("mailbox_diag", "mbd", mailbox_diag_command, "MailBoxDiag"),

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_COMMANDS_H */
