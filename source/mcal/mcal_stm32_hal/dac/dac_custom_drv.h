#ifndef DAC_CUSTOM_DRV_H
#define DAC_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_mcal.h"
#include "dac_custom_types.h"
#include "stm32fx_hal.h"

#ifndef HAS_DAC
#error "+ HAS_DAC"
#endif

DAC_TypeDef* DacGetDACx(uint8_t num);
bool dac_channel_init(uint8_t dac_num, uint8_t dac_channel);
bool dac_channel_read(uint8_t dac_num, uint16_t dac_channel, uint32_t* const code);

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_DRV_H  */
