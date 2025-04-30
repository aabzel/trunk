#ifndef I2S_ZEPHYR_DRV_H
#define I2S_ZEPHYR_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2c_bsp.h"
#include "i2c_types.h"
#include "i2c_zephyr_const.h"
#include "i2c_zephyr_types.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

struct device* I2sNumToI2sDevPtr(I2sNum_t i2s_num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_ZEPHYR_DRV_H  */
