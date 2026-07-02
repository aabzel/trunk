#ifndef DAC_CHANNEL_CONFIG_H
#define DAC_CHANNEL_CONFIG_H

#include "dac_channel_types.h"

#ifndef HAS_DAC
#error  "+HAS_DAC"
#endif

extern const DacChannelConfig_t DacChannelConfig[];
extern DacChannelHandle_t DacChannelInstance[];

uint32_t dac_channel_get_cnt(void);

#endif /* DAC_CHANNEL_CONFIG_H */
