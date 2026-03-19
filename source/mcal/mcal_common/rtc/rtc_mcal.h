#ifndef RTC_GENERAL_API_H
#define RTC_GENERAL_API_H

#include <time.h>

#include "std_includes.h"
#include "rtc_config.h"
#include "rtc_types.h"
#include "rtc_diag.h"

/*API*/
RtcHandle_t* RtcGetNode(uint8_t num);
const RtcConfig_t* RtcGetConfig(uint8_t num);
const RtcInfo_t* RtcGetInfo(uint8_t num);

bool rtc_mcal_init(void);
bool rtc_init_common(RtcHandle_t* const Node);
bool rtc_init_one(uint8_t num);
bool rtc_ctrl(uint8_t num, bool on_off);
bool RtcIsValidConfig(const RtcConfig_t* const Config);

// setter
bool rtc_adjust_by_build_time(uint8_t num);
bool rtc_external_init_one(uint8_t num);
bool rtc_set(uint8_t num, const struct tm* const time_date);
bool rtc_set_date(uint8_t num, const struct tm* const time_date);
bool rtc_set_time(uint8_t num, const struct tm* const time_date);
bool rtc_external_set(uint8_t num, const struct tm *const DateTime);
bool rtc_external_set_date(uint8_t num, const struct tm* const time_date);
bool rtc_external_set_time(uint8_t num, const struct tm* const time_date);

// getter
bool rtc_get(uint8_t num, struct tm* const time_date);
bool rtc_external_get(uint8_t num, struct tm *const DateTime);
bool rtc_internal_get(uint8_t num, struct tm *const DateTime);

#endif /* RTC_GENERAL_API_H  */
