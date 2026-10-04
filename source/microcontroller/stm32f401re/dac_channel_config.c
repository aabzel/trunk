#include "dac_channel_config.h"

#include "data_utils.h"

static uint16_t SampleMem1[512];
static uint16_t SampleMem2[512];

const DacChannelConfig_t SECTION_CFG_DATA DacChannelConfig[] = {
    {
            .num = 1,
            .scale = 1.0f,
            .Pad = {.port=PORT_A, .pin=4,},
            .name = "DAC_OUT1",
            .channel = 1,
            .dac_num = 1,
            .mode = DAC_MODE_FROM_NONE,
            .dds_num = 0,
            .valid = true,
            .SampleFifoMem = SampleMem1,
            .SampleFifoMemCnt = ARRAY_SIZE(SampleMem1),
    },
    {
            .num = 2,
            .channel = 2,
            .Pad = {.port=PORT_A, .pin=5,},
            .dac_num = 1,
            .dds_num = 1,
            .scale = 1.0f,
            .mode = DAC_MODE_FROM_DDS,
            .name = "DAC_OUT2",
            .valid = true,
            .SampleFifoMem = SampleMem2,
            .SampleFifoMemCnt = ARRAY_SIZE(SampleMem2),
    },
};

DacChannelHandle_t DacChannelInstance[] = {
    { .num = 1, .valid = true,  },
    { .num = 2, .valid = true,  },
};

COMPONENT_GET_CNT(DacChannel, dac_channel)

