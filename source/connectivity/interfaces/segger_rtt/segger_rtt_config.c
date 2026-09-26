#include "segger_rtt_config.h"

#include "data_utils.h"

static uint8_t RxBuffer1[800] = {0};

const SeggerRttConfig_t SeggerRttConfig[] = {
    {
        .num = 1,
        .BufferIndex = 0,
        .RxBuffer = RxBuffer1,
        .buffer_size = ARRAY_SIZE(RxBuffer1),
        .valid = true,
        .name = "CLI",
    },
};

SeggerRttHandle_t SeggerRttInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(SeggerRtt, segger_rtt)

