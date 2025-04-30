#include "wav_config.h"

#include <stddef.h>

#include "data_utils.h"

const WavConfig_t WavConfig[] = {
    {
        .num = 1,
        .valid = true,
        .sampling_frequency_hz = 44100,
        .sample_cnt = 5000,
        .file_name = "track.wav",
        .name = "Rec",
    },
    {
        .num = 2,
        .valid = true,
        .sampling_frequency_hz = 44100,
        .sample_cnt = 5000,
        .file_name = "track.wav",
        .name = "pulse",
    },
};

WavHandle_t WavInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

uint32_t wav_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(WavConfig);
    uint32_t cnt_ints = ARRAY_SIZE(WavInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
