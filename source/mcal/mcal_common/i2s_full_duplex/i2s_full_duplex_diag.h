#ifndef I2S_FULL_DUPLEX_GENERAL_DIAG_H
#define I2S_FULL_DUPLEX_GENERAL_DIAG_H

#include "std_includes.h"

#include "i2s_full_duplex_types.h"

const char*  I2sFullDuplexInputToStr(I2sFullDuplexInputs_t input);
const char*  I2sFullDuplexStateToStr(I2sFullDuplexState_t state);
const char* I2sFullDuplexToStr(const I2sFullDuplexConfig_t* const Config);
bool I2sFullDuplexDiagConfig(const I2sFullDuplexConfig_t* const Config);
bool i2s_full_duplex_diag(void);

#endif /* I2S_FULL_DUPLEX_GENERAL_DIAG_H */
