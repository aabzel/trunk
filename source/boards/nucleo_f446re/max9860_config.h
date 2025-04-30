
#ifndef MAX9860_CONFIG_H
#define MAX9860_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_types.h"

#ifndef HAS_MAX9860
#error "+HAS_MAX9860"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

extern Max9860Item_t Max9860Item;
extern const Max9860Config_t Max9860Config;
extern const Max9860RegVal_t Max9860RegValConfigLUT[];
extern Max9860RegVal_t Max9860RegVal[MAX9860_REG_CNT];

uint32_t max9860_get_config_cnt(void);

#endif /* MAX9860_CONFIG_H */
