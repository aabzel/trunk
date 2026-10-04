#ifndef LED_MONO_CONFIG_H
#define LED_MONO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#define LED_CNT 1
#define LED_ID_HEARTBEAT LED_STATUS_LED

typedef enum {
    LED_UNDEF = 0,
    LED_ERROR_LED ,
    LED_STATUS_LED ,
} K132RevA_t;

extern const LedMonoConfig_t LedMonoConfig[];
extern LedMonoHandle_t LedMonoInstance[];

uint32_t led_mono_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_CONFIG_H  */
