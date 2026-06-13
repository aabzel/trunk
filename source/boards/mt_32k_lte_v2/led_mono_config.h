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

typedef enum{
    LED_ID_GSM = 1,
    LED_ID_GPS = 2,
    LED_ID_ERROR = 3,
    LED_ID_CAN = 4,
    LED_ID_SIM = 5,
}LedLegalNum_t;

#define LED_ID_HEARTBEAT LED_ID_SIM

extern const LedMonoConfig_t LedMonoConfig[5];
extern LedMonoHandle_t LedMonoInstance[5];

uint32_t led_mono_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_CONFIG_H  */
