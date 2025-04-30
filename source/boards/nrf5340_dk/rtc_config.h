#ifndef RTC_CONFIG_H
#define RTC_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "rtc_types.h"

extern const RtcConfig_t RtcConfig[];
extern RtcHandle_t RtcInstance[];

uint32_t rtc_get_cnt(void);

#endif /* RTC_CONFIG_H  */
