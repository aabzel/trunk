#ifndef AUDIO_TYPES_H
#define AUDIO_TYPES_H

#include <stdint.h>

#include "bit_types.h"
#include "audio_const.h"

#ifdef HAS_DSP
#include "dsp_types.h"
#endif

typedef union{
    uint8_t buff[4];
    struct {
        int16_t left;
        int16_t right;
    };
}AudioStereoSample16bit_t;

#endif /* AUDIO_TYPES_H */
