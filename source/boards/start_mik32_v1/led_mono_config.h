#ifndef LED_MONO_CONFIG_H
#define LED_MONO_CONFIG_H

#include "std_includes.h"
#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#ifndef HAS_LED_MONO
#error "Add HAS_LED_MONO"
#endif

typedef enum{
    LED_ID_HEARTBEAT = 1,
    LED_ID_ERROR = 2,
    LED_ID_UNDEF = 0,
}LedLegalNums_t;

#define LED_HEARTBEAT_ID LED_ID_HEARTBEAT

extern const LedMonoConfig_t LedMonoConfig[2];
extern LedMonoHandle_t LedMonoInstance[2];

uint32_t led_mono_get_cnt(void);
bool led_mono_fix(void);

#endif /* LED_MONO_CONFIG_H  */
