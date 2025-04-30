#ifndef RTC_ISR_H
#define RTC_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrfx_rtc.h"
#include "rtc_types.h"

#ifdef NRFX_RTC0_ENABLED
void nrfx_rtc0_event_handler(nrfx_rtc_int_type_t int_type);
#endif

#ifdef NRFX_RTC1_ENABLED
void nrfx_rtc1_event_handler(nrfx_rtc_int_type_t int_type);
#endif

#ifdef NRFX_RTC2_ENABLED
void nrfx_rtc2_event_handler(nrfx_rtc_int_type_t int_type);
#endif

#ifdef __cplusplus
}
#endif

#endif /* RTC_ISR_H  */
