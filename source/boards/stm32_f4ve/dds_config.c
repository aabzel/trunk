#include "dds_config.h"

#include <stddef.h>

#include "time_mcal.h"
#include "data_utils.h"


static SampleType_t SampleArray[10] = {0};

const DdsConfig_t DdsConfig[] = {
    {
        .num = DDS_DAC_TEST,
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(30),
        .amplitude = 32000,
        .offset = 32000,
        .sample_per_second = 8000,
        .sample_bitness = 12,
        .dds_mode = DDS_MODE_SIN,
        .duty_cycle = 50.0,
        .frequency = 4.0,
        .frequency2 = 14.0,
        .frame_pattern = CHANNEL_MONO,
        .name = "Sin",
        .phase_ms = 0.0,
        .player =  DDS_PLAYER_CSV_FILE,
        .valid = true,

    },


};

DdsHandle_t DdsInstance[] = {
    {
        .num = DDS_DAC_TEST,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dds, dds)
