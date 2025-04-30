#ifndef SW_DAC_TYPES_H
#define SW_DAC_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "sw_dac_const.h"

#ifdef HAS_AUDIO
#include "audio_types.h"
#endif

#define SW_DAC_COMMON_VARIABLE     \
    uint8_t num;                   \
    double phase_ms;               \
    double duty_cycle;             \
    double frequency;              \
    SampleType_t amplitude;        \
    uint32_t sample_per_second;    \
    SwDacMode_t dac_mode;          \
    uint8_t sample_bitness;        \
    FramePattern_t frame_pattern;  \
    SampleType_t offset;

typedef struct {
	SW_DAC_COMMON_VARIABLE
    char* name;
} SwDacConfig_t;

typedef struct {
	SW_DAC_COMMON_VARIABLE
    SampleType_t cur_sample;
    SampleType_t prev_sample;
#ifdef HAS_DTMF
    double frequency2;
#endif

#ifdef HAS_DYNAMIC_SAMPLES
    SampleType_t* tx_sample_array;
#endif

#ifdef HAS_I2S_RX
    SampleType_t* rx_sample_array; /*Do We Need RxSamples*/
#endif

#ifdef HAS_SW_DAC_STATIC_SAMPLES
    SampleType_t tx_sample_static_array[100]; /*ToneFreq:1kHz, Fs: 48kHz, OnePeriod: 1ms, 48 sample, 2 channels*/
#endif /*HAS_SW_DAC_STATIC_SAMPLES*/

#ifdef HAS_REAL_SAMPLE_ARRAY
    SampleType_t* real_sample_array;
#endif
    uint32_t sample_cnt;
    bool init;
} SwDac_t;

#endif /*SW_DAC_TYPES_H*/
