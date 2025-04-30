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

//#define LED_MONO_COUNT  3

#ifdef	HAS_CORE_APP
#define LED_HEARTBEAT_ID 1
#endif/*HAS_CORE_APP*/

extern const LedMonoConfig_t LedMonoConfig[ ];
extern LedHandle_t LedMonoInstance[ ];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONOCHROME_CONFIG_H  */
