#ifndef RTC_DRV_H
#define RTC_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"

extern RTC_HandleTypeDef hrtc;

bool rtc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* RTC_DRV_H  */
