#include "bit_fifo_config.h"

#include "data_utils.h"

static uint8_t Mem1[200];
static uint8_t Mem2[200];

const BitFifoConfig_t BitFifoConfig[] = {
    {
        .num = 1,
        .valid = true,
        .buffer = Mem1,
        .size = sizeof(Mem1),
        .name = "BIT_FIFO1",
    },

    {
        .num = 2,
        .valid = true,
        .buffer = Mem2,
        .size = sizeof(Mem2),
        .name = "BIT_FIFO2",
    },
};

BitFifoHandle_t BitFifoInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

COMPONENT_GET_CNT(BitFifo, bit_fifo)


