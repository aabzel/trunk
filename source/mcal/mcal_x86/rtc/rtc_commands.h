#ifndef RTC_COMMANDS_H
#define RTC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool rtc_diag_command(int32_t argc, char* argv[]);

#define RTC_COMMANDS                                                                  \
        SHELL_CMD("rtc_diag", "rd", rtc_diag_command, "RTC diag"),

#ifdef __cplusplus
}
#endif

#endif /* RTC_COMMANDS_H */
