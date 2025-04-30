#ifndef I2S_ISR_H
#define I2S_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2s_dep.h"
#include "nrfx_i2s.h"

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif

#ifndef HAS_I2S_ISR
#error "+HAS_I2S_ISR"
#endif

extern uint32_t it_busy_cnt;

void NrfxI2s0DataHandler(nrfx_i2s_buffers_t const* p_released, uint32_t status);

#ifdef __cplusplus
}
#endif

#endif /* I2S_ISR_H */
