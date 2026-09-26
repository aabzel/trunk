#ifndef LED_MONO_CONFIG_H
#define LED_MONO_CONFIG_H

#include "std_includes.h"
#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#define LED_ID_GREEN 1
#define LED_ID_HEARTBEAT 1

extern const LedMonoConfig_t LedMonoConfig[];
extern LedMonoHandle_t LedMonoInstance[];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONO_CONFIG_H  */
