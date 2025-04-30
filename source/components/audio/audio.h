#ifndef AUDIO_MCAL_H
#define AUDIO_MCAL_H

#include "std_includes.h"
#ifdef HAS_DSP
#include "dsp_types.h"
#endif
#include "audio_types.h"

bool audio_add_front_zeros( SampleType_t* const SampleArray,  uint32_t size,int32_t offset );
uint32_t sample_int_2_uint(int32_t sample, uint8_t bits);

#endif /* AUDIO_MCAL_H */
