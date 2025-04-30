#ifndef I2S_NRF_TYPES_H
#define I2S_NRF_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2s_nrf_const.h"
#include "nrf_i2s.h"
#include "nrfx_i2s.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

#define I2S_CUSTOM_VARIABLES  \
    volatile nrfx_i2s_buffers_t i2s_buffers[I2S_ARRAY_CNT];

typedef struct {
    nrf_i2s_mck_t nrf_i2s_mck;
    uint8_t div_val;
}NrfI2sDiv_t;

typedef struct {
    nrf_i2s_ratio_t nrf_i2s_lrclk;
    uint16_t ratio_val;
}NrfI2sLrDiv_t;

#ifdef __cplusplus
}
#endif

#endif /* I2S_NRF_TYPES_H */
