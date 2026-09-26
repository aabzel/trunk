#include "bin_dac_config.h"

#include "data_utils.h"

static uint32_t GPIOxBSRR[BIN_DAC_TX_SIZE] = {0};
static uint8_t TxBitFifoMem1[5000] = {0};

const BinDacConfig_t BinDacConfig[] = {
    {
        .num = 1,
        .data_array_size = ARRAY_SIZE(GPIOxBSRR),
        .GpioPortDataArray = GPIOxBSRR,
        .DmaChPad = { .name = "GPIOtx", .priority = 0, .dma_num = 2, .stream = 5,  .channel = 6, },
        .debugPad = {.port = PORT_F, .pin = 1,},
        .outPad = {.port = PORT_A, .pin = 4,},
        .part_size = 1+8+1+2,
        .timer_num = 1,
        .tx_fifo_mem_size = ARRAY_SIZE(TxBitFifoMem1),
        .TxFifoMem = TxBitFifoMem1,
        .sample_freq_hz = 9600,
        .valid = true,
        .name = "BIN_DAC1",
    },
};


BinDacHandle_t BinDacInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(BinDac, bin_dac)


