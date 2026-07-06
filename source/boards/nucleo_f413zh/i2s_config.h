#ifndef I2S_CONFIG_H
#define I2S_CONFIG_H

#include "i2s_types.h"
#include "sys_config.h"

extern I2sConfig_t I2sConfig[]; /*For Mux config between NorFlash Or FlashFs*/
extern I2sHandle_t I2sInstance[];

uint32_t i2s_get_cnt(void);

#endif /* I2S_CONFIG_H  */
