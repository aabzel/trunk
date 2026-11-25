#ifndef CAN_CUSTOM_COMMANDS_H
#define CAN_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


bool can_diag_low_level_command(int32_t argc, char* argv[]);
bool can_diag_ram_command(int32_t argc, char* argv[]);
bool can_diag_mail_box_command(int32_t argc, char* argv[]);
bool can_raw_reg_command(int32_t argc, char* argv[]);
bool can_diag_wakeup_message_buffers_command(int32_t argc, char* argv[]);



#define CAN_CUSTOM_COMMANDS                                                                        \
    SHELL_CMD("can_raw_reg", "canra", can_raw_reg_command, "CanRawReg"),                          \
    SHELL_CMD("can_diag_ram", "cdr", can_diag_ram_command, "CanDiagRam"),                          \
    SHELL_CMD("can_diag_wkp_mess_buf", "cdwmb", can_diag_wakeup_message_buffers_command, "CanDiagWakeUpMessBuff"),          \
    SHELL_CMD("can_diag_mail_box", "cdmb", can_diag_mail_box_command, "CanDiagMailBox"),          \
    SHELL_CMD("can_diag_low_level", "candl", can_diag_low_level_command, "CanDiagLowLevel"),




#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_COMMANDS_H */
