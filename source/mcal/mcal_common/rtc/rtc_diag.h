#ifndef RTC_DIAG_H
#define RTC_DIAG_H

#include <stdbool.h>

#include "rtc_types.h"

bool rtc_diag(void);
bool RtcDiagConfig(const RtcConfig_t* const Config);
const char* RtcConfigToStr(const RtcConfig_t* const Config);
const char* rtc_get_str(const uint8_t rtc_num);

#endif /* RTC_DIAG_H */
