#ifndef ECHO_EFFECT_ISR_H
#define ECHO_EFFECT_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "audio_types.h"


bool echo_effect_proc_sample_volume(uint8_t num, SampleType_t sample_in, SampleType_t* const sample_out) ;
bool echo_effect_proc_sample(uint8_t num, SampleType_t sample_in,
                                 SampleType_t* const sample_out);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ECHO_EFFECT_ISR_H*/
