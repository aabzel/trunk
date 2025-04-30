#ifndef I2S_ZEPHYR_TYPES_H
#define I2S_ZEPHYR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_zephyr_const.h"

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

typedef struct {
	I2sNum_t i2s_num;
	struct device* I2sDev;
}I2sInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* I2S_ZEPHYR_TYPES_H  */
