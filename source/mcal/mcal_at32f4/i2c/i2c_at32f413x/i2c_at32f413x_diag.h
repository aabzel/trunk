#ifndef I2C_AT32F413X_DIAG_H
#define I2C_AT32F413X_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_f413x_register_types.h"

const char* I2cAt32f413xRegSts1ToStr(const I2cAt32F413xRegSts1_t* const Node);
const char* I2cAt32f413xRegSts2ToStr(const I2cAt32F413xRegSts2_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* I2C_AT32F413X_DIAG_H */




