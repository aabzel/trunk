#ifndef I2S_NRF53_DRIVER_H
#define I2S_NRF53_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_nrf_types.h"
#include "i2s_types.h"

#ifndef HAS_NRF53
#error "+HAS_NRF53"
#endif

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif


#ifdef __cplusplus
}
#endif

#endif /* I2S_NRF53_DRIVER_H */
