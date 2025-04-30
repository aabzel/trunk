#ifndef I2C_ISR_H
#define I2C_ISR_H

#include <stdbool.h>
#include <stdint.h>

bool I2cTxDoneIsr(uint8_t num);
bool I2cRxDoneIsr(uint8_t num);
bool I2cErrorIsr(uint8_t num);

#endif /* I2C_ISR_H */
