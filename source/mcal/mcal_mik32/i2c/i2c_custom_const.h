#ifndef I2C_MIK_CONST_H
#define I2C_MIK_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    I2C_MODE_I2C=0,
    I2C_MODE_SMBUS=1,
}I2cMode_t;

typedef enum {
    I2C_BUS_ROLE_SLAVE=0,
    I2C_BUS_ROLE_MASTER=1,
}I2cBusRole_t;

typedef enum {
    I2C_BUS_STATE_SPARE = 0,
    I2C_BUS_STATE_BUSY = 1,
}I2cBusState_t;

typedef enum {
    I2C_DIR_RX = 0,
    I2C_DIR_TX = 1,
}I2cDir_t;

#ifdef __cplusplus
}
#endif

#endif /* I2C_MIK_CONST_H */
