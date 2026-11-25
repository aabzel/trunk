#ifndef I2C_CUSTOM_ISR_H
#define I2C_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool I2cErrIRQHandler(uint8_t num);
bool I2cEvtIRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_ISR_H */
