#ifndef RTC_CUSTOM_COMMANDS_H
#define RTC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif


bool rtc_int_ctrl_command(int32_t argc, char* argv[]);
bool rtc_diag_low_level_command(int32_t argc, char* argv[]);
bool rtc_cc_set_command(int32_t argc, char* argv[]);
bool rtc_tick_ctrl_command(int32_t argc, char* argv[]);

#define RTC_CUSTOM_COMMANDS                                                               \
    SHELL_CMD("rtc_int_ctrl", "rtic", rtc_int_ctrl_command, "RtcIntCtrl"),                \
    SHELL_CMD("rtc_tick_ctrl", "rttc", rtc_tick_ctrl_command, "RtcTickCtrl"),             \
    SHELL_CMD("rtc_diag_low_lev", "rtdl", rtc_diag_low_level_command, "RtcDiagLowLevel"), \
    SHELL_CMD("rtc_cc_set", "rtcs", rtc_cc_set_command, "RtcCaptureCompareSet"),

#ifdef __cplusplus
}
#endif

#endif /* RTC_CUSTOM_COMMANDS_H */
