#ifndef RTC_GENERAL_COMMANDS_H
#define RTC_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifdef HAS_RTC_CUSTOM_COMMANDS
#include "rtc_internal_commands.h"
#else
#define RTC_CUSTOM_COMMANDS
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool rtc_adjust_command(int32_t argc, char* argv[]);
bool rtc_ctrl_command(int32_t argc, char* argv[]);
bool rtc_diag_command(int32_t argc, char* argv[]);
bool rtc_get_command(int32_t argc, char* argv[]);
bool rtc_set_time_command(int32_t argc, char* argv[]);
bool rtc_set_date_command(int32_t argc, char* argv[]);

#define RTC_COMMANDS                                                                               \
        RTC_CUSTOM_COMMANDS                                                                        \
        SHELL_CMD("rtc_adjust", "rta", rtc_adjust_command, "RtcAdjust"),                           \
        SHELL_CMD("rtc_ctrl", "rtc", rtc_ctrl_command, "RtcCtrl"),                                 \
        SHELL_CMD("rtc_set_time", "rst", rtc_set_time_command, "RtcSetTime"),                      \
        SHELL_CMD("rtc_set_date", "rsd", rtc_set_date_command, "RtcSetDate"),                      \
        SHELL_CMD("rtc_diag", "rtd", rtc_diag_command, "RtcDiag"),                                 \
        SHELL_CMD("rtc_get", "rtg", rtc_get_command, "RtcGet"),                                    \

#ifdef __cplusplus
}
#endif

#endif /* RTC_GENERAL_COMMANDS_H */
