#ifndef LED_MONO_CONFIG_H
#define LED_MONO_CONFIG_H

#include "std_includes.h"
#include "led_mono_types.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

typedef enum {
   LED_ID_GREEN_1 = 1,
   LED_ID_GREEN_2 = 2,
   LED_ID_GREEN_3 = 3,
   LED_ID_GREEN_4 = 4,
   LED_ID_UNDEF = 0,
}LegalLed_t;

#define LED_HEARTBEAT_ID LED_ID_GREEN_1

extern const LedMonoConfig_t LedMonoConfig[];
extern LedMonoHandle_t LedMonoInstance[];

uint32_t led_mono_get_cnt(void);

#endif /* LED_MONO_CONFIG_H  */
