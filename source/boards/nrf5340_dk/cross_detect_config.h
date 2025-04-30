#ifndef CROSS_DETECT_CONFIG_H
#define CROSS_DETECT_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "cross_detect_types.h"

#ifndef HAS_CROSS_DETECT
#error "Add HAS_CROSS_DETECT"
#endif /*HAS_CROSS_DETECT*/

#define CROSS_DETECT_PIN_CNT 33

extern const CrossDetectConfig_t CrossDetectConfig[];
extern CrossDetectHandle_t CrossDetectInstance[];

extern const CrossDetectPinConfig_t CrossDetectPinConfig[CROSS_DETECT_PIN_CNT];
extern CrossDetectResult_t CrossDetectResult[CROSS_DETECT_PIN_CNT ][CROSS_DETECT_PIN_CNT ] ;

uint32_t cross_detect_get_cnt(void);
uint32_t cross_detect_get_pin_cnt(void);

#endif /* CROSS_DETECT_CONFIG_H  */
