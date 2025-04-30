#ifndef RTC_CUSTOM_DRV_H
#define RTC_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "rtc_internal_types.h"
#include "stm32f4xx_hal.h"

bool rtc_internal_init_one(uint8_t num);
bool rtc_internal_set(uint8_t num, const struct tm* const DateTime);
bool rtc_internal_set_time(uint8_t num, const struct tm* const DateTime);
bool rtc_internal_set_date(uint8_t num, const struct tm* const DateTime) ;
bool rtc_internal_get(uint8_t num, struct tm* const DateTime) ;

#ifdef __cplusplus
}
#endif

#endif /* RTC_CUSTOM_DRV_H  */
