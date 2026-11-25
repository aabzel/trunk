#ifndef DAC_CUSTOM_TYPE_H
#define DAC_CUSTOM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "dac_custom_const.h"
#include "microcontroller_const.h"
#include "clock_const.h"
#include "gpio_types.h"

#define DAC_CUSTOM_VARIABLES   dac_select_type DACx;

typedef struct {
    bool valid;
    dac_select_type DACx;
    uint8_t num;
    ClockBus_t clock_bus;
    IRQn_Type irq_n;
    Pad_t Pad;
}DacInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_TYPE_H */
