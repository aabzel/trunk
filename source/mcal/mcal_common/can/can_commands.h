#ifndef CAN_COMMANDS_H
#define CAN_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "debug_info.h"
#include "can_types.h"

#ifndef HAS_CAN
#error "+HAS_CAN"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_CAN_CUSTOM
#include "can_custom_commands.h"
#else
#define CAN_CUSTOM_COMMANDS
#endif


#ifdef HAS_CAN_FD
bool can_fd_send_command(int32_t argc, char* argv[]);
bool can_fd_diag_command(int32_t argc, char* argv[]);

#define CAN_FD_COMMANDS                                                                   \
        SHELL_CMD("can_fd_send", "cfs", can_fd_send_command, "CanFdSendHexStr"),          \
        SHELL_CMD("can_fd_diag", "cafd", can_fd_diag_command, "CanFdDiag"),

#else
#define CAN_FD_COMMANDS
#endif

bool can_parse_mesg(int32_t argc, char* argv[], const int32_t start, CanMessage_t * const Message) ;
bool can_mesg_buff_command(int32_t argc, char* argv[]);
bool can_diag_command(int32_t argc, char* argv[]);
bool can_diag_interrupt_command(int32_t argc, char* argv[]);
bool can_is_my_id_command(int32_t argc, char* argv[]);
bool can_filter_id_mask_diag_command(int32_t argc, char* argv[]);


#define CAN_DIAG_COMMANDS                                                                                      \
        SHELL_CMD("can_diag", "cad", can_diag_command, "CanDiag"),                                             \
        SHELL_CMD("can_filter_diag", "cfim", can_filter_id_mask_diag_command, "CanDiagFilterIdAndMask"),                     \
        SHELL_CMD("can_diag_interrupt", "cadi", can_diag_interrupt_command, "CanDiagInterrupt"),               \
        SHELL_CMD("can_is_my_id", "cimid", can_is_my_id_command, "CanDiagIsMyId"),                                 \
        SHELL_CMD("can_mesg_buff", "cmb", can_mesg_buff_command, "CanDiagMesgBuf"),

bool can_bit_rate_command(int32_t argc, char* argv[]);
bool can_init_command(int32_t argc, char* argv[]);
bool can_send_command(int32_t argc, char* argv[]);
bool can_loopback_command(int32_t argc, char* argv[]);
bool can_loopback_mode_command(int32_t argc, char* argv[]);
bool can_test_loopback_id_command(int32_t argc, char* argv[]);
bool can_calc_bit_rate_command(int32_t argc, char* argv[]);
bool can_rx_frame_manual_command(int32_t argc, char* argv[]);
bool can_send_hi_load_command(int32_t argc, char* argv[]);
bool can_filter_set_command(int32_t argc, char* argv[]);
bool can_send_ext_command(int32_t argc, char* argv[]);
bool can_rx_all_command(int32_t argc, char* argv[]);

#define CAN_SEND_COMMANDS                                                                          \
        SHELL_CMD("can_send", "cs", can_send_command, "CanSendHexStr"),                            \
        SHELL_CMD("can_send_ext", "cse", can_send_ext_command, "CanSendExtHexStr"),                            \
        SHELL_CMD("can_hi_load", "cshl", can_send_hi_load_command, "CanSendHiLoad"),               \
        SHELL_CMD("can_test_loopback_id", "clbi", can_test_loopback_id_command, "CanTestLoopBackId"),

#define CAN_COMMANDS                                                                                           \
        CAN_FD_COMMANDS                                                                                        \
        CAN_SEND_COMMANDS                                                                                      \
        CAN_CUSTOM_COMMANDS                                                                                    \
        CAN_DIAG_COMMANDS                                                                                      \
        SHELL_CMD("can_baud", "cb", can_bit_rate_command, "CanBaud"),                                          \
        SHELL_CMD("can_rx_all", "cra", can_rx_all_command, "CanRxAll"),                                          \
        SHELL_CMD("can_filter_set", "cfims", can_filter_set_command, "CanFilterSet"),                                          \
        SHELL_CMD("can_init", "ci", can_init_command, "CanInit"),                                              \
        SHELL_CMD("can_calc_bit_rate", "ccbr", can_calc_bit_rate_command, "CanCalcBitRate"),                   \
        SHELL_CMD("can_loopback", "clb", can_loopback_command, "CanLoopBack"),                                 \
        SHELL_CMD("can_loopback_mode", "clbm", can_loopback_mode_command, "CanLoopBackMode"),                  \
        SHELL_CMD("can_rx_frame_manual", "crfm", can_rx_frame_manual_command, "CanRxFrameManual"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_COMMANDS_H */
