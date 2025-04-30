#ifndef RTC_CONST_H
#define RTC_CONST_H

#include "rtc_dep.h"

#ifdef HAS_RTC_CUSTOM
#include "rtc_internal_const.h"
#endif

#define RTC_FREQ_HZ (32768)
#define RTC_TICK_PERIOD_S (1.0/32768.0)

typedef enum {
    RTC_LOCATION_INTERNAL = 1,
    RTC_LOCATION_EXTERAL = 2,

    RTC_LOCATION_UNDEF = 0
}RtcLocation_t;

typedef enum {
    RTC_32K_CLOCK_INTERNAL = 1,
    RTC_32K_CLOCK_EXTERAL = 2,
    RTC_32K_CLOCK_UNDEF = 0
}Rtc32kHzClock_t;




typedef enum {
    RTC_FORMAT_12H = 1,
    RTC_FORMAT_24H = 2,
    RTC_FORMAT_UNDEF = 0
}RtcFormat_t;


#endif /* RTC_CONST_H */
