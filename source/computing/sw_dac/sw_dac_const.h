#ifndef SW_DAC_CONST_H
#define SW_DAC_CONST_H

#include "sw_dac_dep.h"

typedef enum {
    DAC_MODE_STATIC = 0U,
    DAC_MODE_PWM = 1U,
    DAC_MODE_SIN = 2U,
    DAC_MODE_SAW = 3U,
    DAC_MODE_FENCE = 4U,
    DAC_MODE_PULSE_TRAIN = 5U,
    DAC_MODE_CHIRP = 6U,
#ifdef HAS_DTMF
    DAC_MODE_DTMF = 7U,
#endif

    DAC_UNDEF = 8U
} SwDacMode_t;

typedef enum {
    CHANNEL_ONLY_RIGHT=1,
    CHANNEL_ONLY_LEFT=2,
    CHANNEL_BOTH=3,

    CHANNEL_UNDEF=0,
}FramePattern_t;

#endif /* SW_DAC_CONST_H*/
