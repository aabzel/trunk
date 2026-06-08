#include "incremental_encoder_config.h"

#include "data_utils.h"

static IncrementalEncoderEvent_t IncEncEventMem[100]={0};

const IncrementalEncoderConfig_t IncrementalEncoderConfig[] = {
    {
        .num = 1,
        .EventMem = IncEncEventMem,
        .event_mem_size = ARRAY_SIZE(IncEncEventMem),
        .PadB = {.port = PORT_E, .pin = 0,},
        .PadA = {.port = PORT_E, .pin = 1,},
        .valid = true,
        .cnt_pre_revolution = 96,//94 96
        .name = "brightness",
    },
};

IncrementalEncoderHandle_t IncrementalEncoderInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(IncrementalEncoder, incremental_encoder)


