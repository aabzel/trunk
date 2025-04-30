#ifndef RTC_CUSTOM_TYPES_H
#define RTC_CUSTOM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "rtc_custom_const.h"
#include "nrfx_rtc.h"

#define RTC_CUSTOM_VARIABLES           \
    nrfx_rtc_t handle;                 \
    nrfx_rtc_handler_t isr_handler;

typedef struct{
    uint8_t num;
    bool valid;
    nrfx_rtc_t handle;
    nrfx_rtc_handler_t event_handler;
    uint8_t counter_bit;
}RtcStaticInfo_t;

#endif /* RTC_CUSTOM_TYPES_H  */
