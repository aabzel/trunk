#ifndef SW_DAC_CONFIG_H
#define SW_DAC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sw_dac_types.h"

#ifndef HAS_SW_DAC
#error  "+HAS_SW_DAC"
#endif /*HAS_SW_DAC*/

#define DAC_I2S_NUM 1
#define DAC_GREEN_LED_NUM 2
#define DAC_RED_LED_NUM 3
#define DAC_DFT_TEST_NUM 4
#define DAC_MODULATOR_NUM 5

extern const SwDacConfig_t SwDacConfig[];
extern SwDac_t SwDacItem[];

uint32_t sw_dac_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SW_DAC_CONFIG_H*/
