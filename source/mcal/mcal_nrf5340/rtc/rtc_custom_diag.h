#ifndef RTC_CUSTOM_DIAG_H
#define RTC_CUSTOM_DIAG_H

#include <stdbool.h>

#include "rtc_custom_types.h"

bool rtc_diag_low_level(void);
bool RtcStaticInfoDiag(const RtcStaticInfo_t* const StaticInfo);

#endif /* RTC_CUSTOM_DIAG_H  */
