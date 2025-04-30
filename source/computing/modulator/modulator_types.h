#ifndef MODULATOR_TYPES_H
#define MODULATOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "audio_types.h"
#include "modulator_const.h"

typedef struct  {
    Modulation_t modulation;
    uint32_t sampling_frequency_hz;
    uint32_t sample_cnt;
    uint32_t symbol_cnt;
    uint32_t sample_per_tone;
    double tone_duration_ms;
    double signal_duration_s;
    double freq_step_hz;
    double amplitude;
    uint8_t base16_chunk[16];
    SampleType_t samples[999];
    uint8_t dac_num;
} Modulator_t;

#ifdef __cplusplus
}
#endif

#endif /*MODULATOR_TYPES_H*/
