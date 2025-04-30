#ifndef I2S_CUSTOM_ISR_H
#define I2S_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"

bool I2sIRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_ISR_H */
