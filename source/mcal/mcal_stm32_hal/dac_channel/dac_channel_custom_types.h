#ifndef DAC_CHANNEL_CUSTOM_TYPES_H
#define DAC_CHANNEL_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_custom_const.h"
//#include "dac_types.h"
#include "gpio_types.h"
#include "stm32fx_hal.h"

#define DAC_CHANNEL_CUSTOM_VARIABLES

typedef struct {
    uint8_t num;
    uint8_t dac_channel;
    uint32_t dac_channel_code;
    Pad_t pad;
    bool valid;
} DacChannelInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* DAC_CHANNEL_CUSTOM_TYPES_H  */
