#ifndef RTC_CUSTOM_COMMANDS_H
#define RTC_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool rtc_internal_diag_command(int32_t argc, char* argv[]);

#define RTC_CUSTOM_COMMANDS                                                                  \
        SHELL_CMD("rtc_diag", "rd", rtc_internal_diag_command, "RtcDiag"),

#ifdef __cplusplus
}
#endif

#endif /* RTC_CUSTOM_COMMANDS_H */
