#include "incremental_encoder_config.h"

#include "data_utils.h"

static IncrementalEncoderEvent_t IncEncEventMem[100]={0};

const IncrementalEncoderConfig_t IncrementalEncoderConfig[] = {
    {
        .limit_down = -1000,
        .limit_up = 1000,
        .divider = 4,
        .num = 1,
        .EventMem = IncEncEventMem,
        .event_mem_size = ARRAY_SIZE(IncEncEventMem),
        .PadB = {.port = PORT_A, .pin = 1,},
        .PadA = {.port = PORT_A, .pin = 2,},
        .valid = true,
        .Scale = STORAGE_SCALE_DECI,
        .Units = STORAGE_UNITS_METER,
        .physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH,
        .cnt_pre_revolution = 96,
        .name = "position",
    },
};

IncrementalEncoderHandle_t IncrementalEncoderInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(IncrementalEncoder, incremental_encoder)


