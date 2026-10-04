#include "wav_config.h"

#include <stddef.h>

#include "file_mcal_config.h"
#include "data_utils.h"

const WavConfig_t WavConfig[] = {
    {
        .num = WAV_NUM_READ,
        .file_num = FILE_MCAL_READ,
        .channels = 2,
        .valid = true,
        .sampling_frequency_hz = 48000,
        .sample_cnt = 10000,
        .file_name_dflt = "out.wav",
        .name = "Play",
    },
    {
        .num = WAV_NUM_WRITE,
        .channels = 2,
        .file_num = FILE_MCAL_WRITE,
        .valid = true,
        .sampling_frequency_hz = 48000,
        .sample_cnt = 5000,
        .file_name_dflt = "track.wav",
        .name = "pulse",
    },

    {
        .num = WAV_NUM_GENERATE,
        .channels = 2,
        .file_num = FILE_MCAL_WRITE,
        .valid = true,
        .sampling_frequency_hz = 48000,
        .sample_cnt = 5000,
        .file_name_dflt = "out.wav",
        .name = "pulse",
    },
};

WavHandle_t WavInstance[] = {
    {        .num = WAV_NUM_READ,        .valid = true,    },
    {        .num = WAV_NUM_WRITE,        .valid = true,    },
    {        .num = WAV_NUM_GENERATE,        .valid = true,    },
};

COMPONENT_GET_CNT(Wav, wav)

