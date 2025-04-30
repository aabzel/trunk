#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "i2s_types.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

extern const I2sConfig_t I2sConfig[1];
/*TODO: Move I2sConfig to Stack*/
extern I2sHandle_t I2sInstance[1];

uint32_t i2s_get_cnt(void);

#endif /* I2S_CONFIG_H  */
