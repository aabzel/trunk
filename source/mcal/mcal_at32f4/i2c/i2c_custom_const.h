#ifndef I2C_CUSTOM_CONST_H
#define I2C_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "artery_at32f4xx.h"

#define I2C_TIMEOUT 0xFFFFFFFF
#define I2C_CHECK_TIMEOUT 0x7FFF

#ifdef HAS_AT32F413
#define I2C_ALL_INT (I2C_DATA_INT|I2C_EVT_INT|I2C_ERR_INT)
#endif


#ifdef HAS_AT32F43X
#define I2C_ALL_INT (I2C_TD_INT|I2C_RD_INT|I2C_ADDR_INT|I2C_ACKFIAL_INT|I2C_STOP_INT|I2C_TDC_INT|I2C_ERR_INT)
#endif //HAS_AT32F43X

typedef enum {
    I2C_MODE_I2C = 0,
    I2C_MODE_SMBUS = 1,
} I2cMode_t;

typedef enum {
    I2C_BUS_ROLE_SLAVE = 0,
    I2C_BUS_ROLE_MASTER = 1,
} I2cBusRole_t;

typedef enum {
    I2C_BUS_STATE_SPARE = 0,
    I2C_BUS_STATE_BUSY = 1,
} I2cBusState_t;

typedef enum {
    I2C_DIR_RX = 0,
    I2C_DIR_TX = 1,
} I2cDir_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_CONST_H */
