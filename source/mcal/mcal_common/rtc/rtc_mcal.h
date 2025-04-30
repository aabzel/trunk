#ifndef RTC_GENERAL_API_H
#define RTC_GENERAL_API_H

#include <stdbool.h>
#include <time.h>

#include "rtc_config.h"
#include "rtc_types.h"
#include "rtc_diag.h"

bool rtc_mcal_init(void);
RtcHandle_t* RtcGetNode(uint8_t num);
const RtcConfig_t* RtcGetConfig(uint8_t num);
const RtcInfo_t* RtcGetInfo(uint8_t num);

bool rtc_init_common(RtcHandle_t* const Node);
bool rtc_ctrl(uint8_t num, bool on_off);
bool rtc_init_one(uint8_t num);
bool RtcIsValidConfig(const RtcConfig_t* const Config);

// setter
bool rtc_set_date(uint8_t num, const struct tm* const time_date);
bool rtc_set(uint8_t num, const struct tm* const time_date);
bool rtc_set_time(uint8_t num, const struct tm* const time_date);
bool rtc_adjust_by_build_time(uint8_t num);

// getter
bool rtc_get(uint8_t num, struct tm* const time_date);


#endif /* RTC_GENERAL_API_H  */
