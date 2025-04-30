#ifndef I2C_ZEPHYR_TYPES_H
#define I2C_ZEPHYR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2c_custom_const.h"

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

typedef struct{
    I2cNum_t num;
    struct device* dev;
    bool valid;
}I2cInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_ZEPHYR_TYPES_H  */
