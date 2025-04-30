#ifndef DAC_CONFIG_H
#define DAC_CONFIG_H

#include "dac_types.h"

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif

extern const DacConfig_t DacConfig[];
extern DacHandle_t DacInstance[];

uint32_t dac_get_cnt(void);

#endif /* DAC_CONFIG_H  */
