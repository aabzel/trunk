#include "sound_recorder_config.h"

#include "data_utils.h"

__attribute__((aligned(8)))
volatile SampleType_t RxSampleArrayMem[REC_MEM_SAM_CNT] = {0} ;

const SoundRecorderConfig_t SoundRecorderConfig[] = {
    {
        .num = 1,
        .i2s_num = 2,
        .RxSampleArray = RxSampleArrayMem,
        .rx_sample_array_size = ARRAY_SIZE(RxSampleArrayMem),
        .sample_freq_hz = 96000,
        .frame_pattern = CHANNEL_BOTH,
        .sample_bitness = 16,
        .valid = true,
        .name = "SOUND_RECORDER1",
    },
};

SoundRecorderHandle_t SoundRecorderInstance[] = {
    {        .num = 1,        .valid = true,    },
};

COMPONENT_GET_CNT(SoundRecorder, sound_recorder)


