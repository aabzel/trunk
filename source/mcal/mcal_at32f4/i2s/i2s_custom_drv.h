#ifndef I2S_CUSTOM_DRIVER_H
#define I2S_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "i2s_custom_types.h"
#include "microcontroller_const.h"
#include "mcal_types.h"

extern const Reg32_t I2sReg[];

bool i2s_write_wait(uint8_t num, uint16_t* array, uint16_t tx_data);
uint32_t i2s_reg_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_DRIVER_H */
