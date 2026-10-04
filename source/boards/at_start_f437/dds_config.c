#include "dds_config.h"

#include <stddef.h>

#include "time_mcal.h"
#include "data_utils.h"


static SampleType_t SampleArray[512] = {0};

const DdsConfig_t DdsConfig[] = {
    {
        .num = DDS_NUM_SIN,
        .player =   { .interface_name = INTERFACE_NAME_I2S, .num=2, },
        .sample_array = SampleArray ,
        .total_sample_cnt = ARRAY_SIZE(SampleArray),
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(30),
        .sample_bitness = 16,
        .dds_mode = DDS_MODE_SIN,
        .offset = 0,
        .amplitude = 30000,
        .sample_per_second = 96000,
        .duty_cycle = 50.0,
        .frequency = 1000.0,
        .frequency2 = 500.0,
        .frame_pattern = CHANNEL_BOTH,
        .name = "Sin",
        .phase_ms = 0.0,
        .valid = true,
    },
};

DdsHandle_t DdsInstance[] = {
    {
        .num = DDS_NUM_SIN,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dds, dds)
