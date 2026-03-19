#ifndef I2C_DIAG_H
#define I2C_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2c_types.h"

#ifdef HAS_I2C_CUSTOM_DIAG
#include "i2c_custom_diag.h"
#endif

bool i2c_diag_one(uint8_t num);
bool i2c_diag(void);
bool i2c_scan_diag(uint8_t num);
const char* I2cConfigToStr(const I2cConfig_t* const Config);
const char* I2cSignalToStr(const I2cSignal_t Signal);

#ifdef __cplusplus
}
#endif

#endif /* I2C_DIAG_H */
