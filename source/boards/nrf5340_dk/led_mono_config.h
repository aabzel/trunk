#ifndef LED_MONOCHROME_CONFIG_H
#define LED_MONOCHROME_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

//#define LED_CNT  2

#ifdef	HAS_CORE_APP
#define LED_HEARTBEAT_ID 1
#endif/*HAS_CORE_APP*/

#ifdef	HAS_CORE_NET
#define LED_HEARTBEAT_ID 3
#endif /*HAS_CORE_NET*/

extern const LedMonoConfig_t LedMonoConfig[ ];
extern LedHandle_t LedMonoInstance[ ];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONOCHROME_CONFIG_H  */
