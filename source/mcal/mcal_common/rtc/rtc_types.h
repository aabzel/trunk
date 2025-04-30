#ifndef RTC_TYPES_H
#define RTC_TYPES_H

#include <time.h>

#include "std_includes.h"
#include "rtc_const.h"
#include "rtc_internal_types.h"

#define RTC_COMMON_VARIABLES       \
    RtcLocation_t rtc_location;    \
    Rtc32kHzClock_t ref_clock;     \
    RtcFormat_t format;            \
    uint8_t num;                   \
    uint8_t irq_priority;          \
    char* name;                    \
    bool valid;

typedef struct {
    RTC_COMMON_VARIABLES
} RtcConfig_t;

typedef struct {
    RTC_COMMON_VARIABLES
    RTC_CUSTOM_VARIABLES
    struct tm TimeDate;
    bool init_done;

    volatile uint32_t error_cnt;
    volatile uint32_t int_cnt;
    uint32_t raw_sec;
} RtcHandle_t;

#endif /* RTC_TYPES_H */
