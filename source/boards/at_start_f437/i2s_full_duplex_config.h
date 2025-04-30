#ifndef I2S_FULL_DUPLEX_CONFIG_H
#define I2S_FULL_DUPLEX_CONFIG_H

#include "i2s_full_duplex_types.h"

extern const I2sFullDuplexConfig_t I2sFullDuplexConfig[];
extern I2sFullDuplexHandle_t I2sFullDuplexInstance[];

uint32_t i2s_full_duplex_get_cnt(void);

#endif /* I2S_FULL_DUPLEX_CONFIG_H  */
