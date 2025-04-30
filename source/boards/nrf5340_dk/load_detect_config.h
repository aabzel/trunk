#ifndef LOAD_DETECT_CONFIG_H
#define LOAD_DETECT_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "load_detect_types.h"

#ifndef HAS_LOAD_DETECT
#error "Add HAS_LOAD_DETECT"
#endif /*HAS_LOAD_DETECT*/

extern const LoadDetectConfig_t LoadDetectConfig[];
extern LoadDetectHandle_t LoadDetectInstance[];

extern const LoadDetectPinConfig_t LoadDetectPinConfig[];
extern LoadDetectPinInfo_t LoadDetectPinInstance[];

uint32_t load_detect_get_cnt(void);
uint32_t load_detect_get_pin_cnt(void);

#endif /* LOAD_DETECT_CONFIG_H  */
