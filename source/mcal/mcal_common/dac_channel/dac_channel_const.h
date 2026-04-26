#ifndef DAC_CHANNEL_GENERAL_CONST_H
#define DAC_CHANNEL_GENERAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_DAC_CHANNEL_CUSTOM
#include "dac_channel_custom_const.h"
#endif

#include "dac_channel_dep.h"
#include "bit_const.h"
#include "time_mcal.h"

//8kHz -> T=0.125*e-3 s = 0.125 ms = 125 us
#define DAC_CHANNEL_POLL_PERIOD_US 31

typedef enum {
    DAC_MODE_FROM_FIFO = 1,
    DAC_MODE_FROM_DDS = 2,
    DAC_MODE_FROM_NONE = 3,
    DAC_MODE_FROM_UNDEF = 0,
} DacMode_t;


typedef enum {
    DAC_CHAN_0 = 0,
    DAC_CHAN_1 = 1,
    DAC_CHAN_2 = 2,
    DAC_CHAN_UNDEF = 0xFF,
} DacChannel_t;

#ifdef __cplusplus
}
#endif

#endif /* DAC_GENERAL_CONST_H  */
