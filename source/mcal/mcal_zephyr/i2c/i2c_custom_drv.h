#ifndef I2C_ZEPHYR_DRV_H
#define I2C_ZEPHYR_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2c_bsp.h"
#include "i2c_types.h"
#include "i2c_custom_const.h"
#include "i2c_custom_types.h"

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

bool i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_ZEPHYR_DRV_H  */
