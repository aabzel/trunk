#ifndef RTC_CUSTOM_DRV_H
#define RTC_CUSTOM_DRV_H

#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "rtc_custom_types.h"

extern const RtcStaticInfo_t RtcStaticInfoLut[];
RtcStaticInfo_t* RtcGetStaticNode(uint8_t num);
bool rtc_set_date_custom(uint8_t num, const struct tm* const time_date);
bool rtc_set_custom(uint8_t num, const struct tm* const time_date);
bool rtc_set_time_custom(uint8_t num, const struct tm* const time_date);
bool rtc_tick_ctrl(uint8_t num,  bool on_off);
bool rtc_get_custom(uint8_t num, struct tm* const time_date);

#endif /* RTC_CUSTOM_DRV_H  */
