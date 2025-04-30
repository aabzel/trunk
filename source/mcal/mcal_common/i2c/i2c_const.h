#ifndef I2C_GENERAL_CONST_H
#define I2C_GENERAL_CONST_H

#include "i2c_dep.h"

#define I2C_POLL_PERIOD_US 10000
#define I2C_SEND_TIME_OUT_MS 100U
#define I2C_READ_TIME_OUT_MS 100U

typedef enum {
    I2C_START=0,
    I2C_STOP=1,
}I2cSignal_t;

#endif /* I2C_GENERAL_CONST_H */
