#ifndef LED_MONOCHROME_CONFIG_H
#define LED_MONOCHROME_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#ifndef HAS_LED_MONO
#error "Add HAS_LED_MONO"
#endif /*HAS_LED_MONO*/

#define LED_CNT 2

#define LED_RED_ID 1
#define LED_YELLOW_ID 2

#define LED_HEARTBEAT_ID LED_YELLOW_ID

extern const LedMonoConfig_t LedMonoConfig[LED_CNT];
extern LedHandle_t LedMonoInstance[LED_CNT];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONOCHROME_CONFIG_H  */
