#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "i2s_types.h"
#include "sys_config.h"

typedef enum {
    I2S_1=1,
    I2S_2=2,
    I2S_3=3,
    I2S_4=4,
    I2S_5=5,
    I2S_6=6,
}I2sNums_t;

extern const I2sConfig_t I2sConfig[];
extern I2sHandle_t I2sInstance[];

uint32_t i2s_get_cnt(void);

#endif /* I2S_CONFIG_H  */
