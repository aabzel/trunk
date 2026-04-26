#ifndef DAC_CHANNEL_CUSTOM_DRV_H
#define DAC_CHANNEL_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_mcal.h"
#include "dac_custom_types.h"
#include "stm32f4xx_hal.h"

#ifndef HAS_DAC_CHANNEL
#error "+ HAS_DAC_CHANNEL"
#endif

DAC_TypeDef* DacGetDACx(uint8_t num);
bool dac_channel_init(uint8_t dac_num, uint8_t dac_channel);
bool dac_channel_read(uint8_t dac_num, uint16_t dac_channel, uint32_t* const code);

#ifdef __cplusplus
}
#endif

#endif /* DAC_CHANNEL_CUSTOM_DRV_H  */
