#ifndef AUDIO_TYPES_H
#define AUDIO_TYPES_H

#include <stdint.h>

#include "bit_types.h"
#include "audio_const.h"
#include "dsp_types.h"

typedef struct{
    int16_t left;
    int16_t right;
}AudioStereoSample16bit_t;

#endif /* AUDIO_TYPES_H */
