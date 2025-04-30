#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2c_types.h"

#ifndef HAS_GPIO
#error "+HAS_I2C"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

bool i2c_init_ll(uint8_t i2c_num);
bool i2c_init(void);
bool i2c_write_wait(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len);
bool i2c_read(uint8_t i2c_num, uint8_t i2c_addr, uint8_t* array, uint16_t array_len);
bool i2c_check_addr(uint8_t i2c_num, uint8_t i2c_addr);
bool i2c_send_signal(uint8_t i2c_num, I2cSignal_t signal);

#ifdef __cplusplus
}
#endif

#endif /* I2C_DRIVER_H */
