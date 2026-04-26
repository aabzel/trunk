#ifndef DAC_CUSTOM_TYPES_H
#define DAC_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_custom_const.h"
//#include "dac_types.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"

#define DAC_CUSTOM_VARIABLES  \
       DAC_HandleTypeDef dac_h;

typedef struct {
    uint8_t num;
    uint8_t dac_channel;
    uint32_t dac_channel_code;
    Pad_t pad;
    bool valid;
} DacChannelInfo_t;

typedef struct {
    uint8_t resolution;
    uint32_t code;
    bool valid;
} DacResolutionInfo_t;

typedef struct {
    uint8_t resolution;
    uint8_t num;
    DAC_TypeDef *DACx;
    IRQn_Type irq_n;
    bool valid;
} DacInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_TYPES_H  */
