#include "dds_config.h"

#include <stddef.h>

#include "time_mcal.h"
#include "data_utils.h"


static SampleType_t SampleArray[3400] = {0};

const DdsConfig_t DdsConfig[] = {
    {
        .num = DDS_NUM_CHIRP,
        .dds_mode = DDS_MODE_CHIRP,
        .player =   { .interface_name = INTERFACE_NAME_I2S, .num = 2, },
        .sample_array = SampleArray ,
        .total_sample_cnt = ARRAY_SIZE(SampleArray),
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(70),
        .sample_bitness = 16,
        .offset = 0,
        .amplitude = 400,
        .sample_per_second = 48000,
        .duty_cycle = 50.0,
        .frequency = 1000.0,
        .frequency2 = 10000.0,
        .frame_pattern = CHANNEL_MONO,//CHANNEL_MONO
        .name = "Sin",
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .num = DDS_NUM_SIN,
        .dds_mode = DDS_MODE_SIN,
        .player =   { .interface_name = INTERFACE_NAME_I2S, .num = 2, },
        .sample_array = SampleArray ,
        .total_sample_cnt = ARRAY_SIZE(SampleArray),
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(70),
        .sample_bitness = 16,
        .offset = 0,
        .amplitude = 400,
        .sample_per_second = 48000,
        .duty_cycle = 50.0,
        .frequency = 1000.0,
        .frequency2 = 10000.0,
        .frame_pattern = CHANNEL_MONO,//CHANNEL_MONO
        .name = "Sin",
        .phase_ms = 0.0,
        .valid = true,
    },
};

DdsHandle_t DdsInstance[] = {
    {
        .num = DDS_NUM_CHIRP,
        .valid = true,
    },
    {
        .num = DDS_NUM_SIN,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dds, dds)
