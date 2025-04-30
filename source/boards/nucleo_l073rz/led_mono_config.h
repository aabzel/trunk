#ifndef LED_MONO_CONFIG_H
#define LED_MONO_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#define LED_CNT  1

#define LED_GREEN_ID 1

#define LED_HEARTBEAT_ID LED_GREEN_ID

extern const LedMonoConfig_t LedMonoConfig[];
extern LedHandle_t LedMonoInstance[];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONO_CONFIG_H  */
