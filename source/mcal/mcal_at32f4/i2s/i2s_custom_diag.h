#ifndef I2S_CUSTOM_DIAG_H
#define I2S_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "i2s_types.h"
#include "artery_at32f4xx.h"

const char* I2sOdd2Str(uint8_t code);
const char* I2sBit2Str(uint8_t code);
const char* SerialMode2Str(uint8_t code);
const char* I2sStd2Str(uint8_t code);
const char* I2sChlen2Str(uint8_t code);

bool i2s_diag_custom(void);
bool i2s_diag_low_level(uint8_t num, char* keyword);
bool i2s_raw_reg_diag(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_DIAG_H */
