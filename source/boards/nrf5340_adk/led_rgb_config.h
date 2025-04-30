#ifndef LED_RGB_CONFIG_H
#define LED_RGB_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_rgb_types.h"

#ifndef HAS_LED_RGB
#error "Add HAS_LED_RGB"
#endif /*HAS_LED*/


#define LED_HEARTBEAT_ID 1


extern const LedRgbConfig_t LedRgbConfig[];
extern LedRgbHandle_t LedRgbItem[];

uint32_t led_rgb_get_cnt(void);

#endif /* LED_RGB_CONFIG_H  */
