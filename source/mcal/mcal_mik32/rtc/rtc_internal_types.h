#ifndef RTC_CUSTOM_TYPES_H
#define RTC_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mik32_hal.h"
#include "rtc_internal_const.h"

#define RTC_CUSTOM_VARIABLES   \
    RTC_HandleTypeDef h_rtc;

typedef struct {
    bool valid;
    uint8_t num;
    ClockBus_t clock_bus;
    RTC_TypeDef *RTCx;
    IRQn_Type wkup_irq_n;
    IRQn_Type alarm_irq_n;
}RtcInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* RTC_CUSTOM_TYPES_H  */
