#ifndef I2C_ISR_H
#define I2C_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "nrfx_twim.h"

nrfx_twim_evt_handler_t I2cNum2IsrHandler(uint8_t num);


#ifdef __cplusplus
}
#endif

#endif /* I2C_ISR_H */
