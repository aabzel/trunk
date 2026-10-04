#ifndef AUDIO_MCAL_H
#define AUDIO_MCAL_H

#include "std_includes.h"
#include "audio_types.h"
#include "audio_diag.h"

#ifdef HAS_DSP
#include "dsp_types.h"
#endif

uint32_t audio_duration_to_samples(uint32_t sampling_frequency_hz, float duratuin_s);
float audio_samples_to_duration_s(const uint32_t sampling_frequency_hz, const uint32_t samples);

float audio_sample_tof_path_m(const  uint32_t sampling_frequency_hz, const float speed_mps);
bool wav_file_name_generate(char* file_name, uint32_t size, uint32_t param,  float duration_s);
bool audio_is_valid_frequency(const uint32_t audio_frequency_hz) ;
bool audio_add_front_zeros( SampleType_t* const SampleArray,  uint32_t size,int32_t offset );
uint32_t sample_int_2_uint(int32_t sample, uint8_t bits);

#endif /* AUDIO_MCAL_H */
