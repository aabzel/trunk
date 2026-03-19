#ifndef I2C_DATABASE_H
#define I2C_DATABASE_H

#include <stdint.h>

const char* I2cGetChipName(uint8_t chip_addr);
uint32_t i2c_get_databse_cnt(void);

#endif /* I2C_DATABASE_H */
