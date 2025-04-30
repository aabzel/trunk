#ifndef I2C_DIAG_H
#define I2C_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2c_types.h"

#include "i2c_custom_diag.h"

bool i2c_scan_diag(uint8_t num);
const char* I2cConfigToStr(const I2cConfig_t* const Config);
bool i2c_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_DIAG_H */
