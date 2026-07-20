#include "loopback_audio_config.h"

#include "data_utils.h"

__attribute__((aligned(8)))
static volatile SampleType_t RxSampleArrayMem[LOOPBACK_MEM_SAM_CNT] = {0} ;

__attribute__((aligned(8)))
static volatile SampleType_t TxSampleArrayMem[LOOPBACK_MEM_SAM_CNT] = {0} ;


const LoopbackAudioConfig_t LoopbackAudioConfig[] = {
    {
        .TxSampleArray = TxSampleArrayMem,
        .RxSampleArray = RxSampleArrayMem,
        .sample_array_size = ARRAY_SIZE(TxSampleArrayMem),
        .rec_num = 1,
        .player_num = 1,
        .led_num = 1,
        .num = 1,
        .valid = true,
        .name = "LoopBackAudio",
    },
};

LoopbackAudioHandle_t LoopbackAudioInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(LoopbackAudio, loopback_audio)


