#include "wav_player_config.h"

#include "data_utils.h"


static SampleType_t PlaySampleArray[PLAYER_MEM_SIZE]={0};

const WavPlayerConfig_t WavPlayerConfig[] = {
    {
        .audio_codec_num = 1,
        .wm8731_num = 1,
        .fat_fs_num = 1,
        .led_num = 1,
        .i2s_num = 2,
        .num = 1,
        .SampleArray = PlaySampleArray,
        .sample_array_size = ARRAY_SIZE(PlaySampleArray),
        .valid = true,
        .name = "WAV_PLAYER1",
    },
};

WavPlayerHandle_t WavPlayerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(WavPlayer, wav_player)


