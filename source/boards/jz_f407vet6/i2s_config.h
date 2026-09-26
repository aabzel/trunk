#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "i2s_types.h"


extern const I2sConfig_t I2sConfig[];
extern I2sHandle_t I2sInstance[];

uint32_t i2s_get_cnt(void);

bool I2s4CallBackTxHalf(void);
bool I2s4CallBackTxDone(void);

#endif /* I2S_CONFIG_H  */
