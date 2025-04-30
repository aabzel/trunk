#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include "i2c_types.h"
#include "sys_config.h"

#ifndef HAS_I2C
#error "+ HAS_I2C"
#endif

extern const I2cConfig_t I2cConfig[];
extern I2cHandle_t I2cInstance[];

uint32_t i2c_get_cnt(void);

#endif /* I2C_CONFIG_H  */
