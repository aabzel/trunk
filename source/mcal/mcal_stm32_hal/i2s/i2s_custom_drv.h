#ifndef I2S_CUSTOM_DRIVER_H
#define I2S_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "i2s_types.h"
#include "i2s_custom_types.h"
#include "stm32fx_hal.h"

extern const I2sInfo_t I2sInfo[];

bool i2s_prescaler_get(uint8_t num  , I2sReg_SPI_I2SPR_t * const pReg);
bool i2s_prescaler_set(uint8_t num , uint8_t i2s_div, bool odd, bool master_clk_out);
const I2sInfo_t* I2sGetInfo(uint8_t num);
I2S_HandleTypeDef* i2s_num_to_handle(uint8_t num);
uint32_t i2s_info_get_cnt(void);
SPI_TypeDef* I2sGetBaseAddr(uint8_t num);


#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_DRIVER_H */
