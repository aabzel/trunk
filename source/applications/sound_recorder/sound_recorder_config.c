#include "sound_recorder_config.h"

#include "data_utils.h"
#include "audio_const.h"

__attribute__((aligned(8)))
static volatile SampleType_t RxSampleArrayMem[REC_MEM_SAM_CNT] = {0} ;

//__attribute__((aligned(8)))
//static volatile SampleType_t FixedRxSampleArrayMem[REC_MEM_SAM_CNT] = {0} ;

const SoundRecorderConfig_t SoundRecorderConfig[] = {
    {
        .num = 1,
        .i2s_num = 2,
        .led_num = 1,
        .RxSampleArray = RxSampleArrayMem,
        .rx_sample_array_size = ARRAY_SIZE(RxSampleArrayMem),
        .sample_freq_hz = AUDIO_FREQ_48K,
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


