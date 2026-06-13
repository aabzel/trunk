#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif

#include "data_utils.h"
#include "spi_types.h"
#include "dma_channel_config.h"

const SpiConfig_t SECTION_CFG_DATA SpiConfig[] = {
#ifdef HAS_SPI2
    {
        .num = 2,
        .name = "W25Q128",
        .bit_rate_hz = 200000,
        .valid = true,
        .frame_size = 8,
        .bit_order = BIT_ORDER_MSB,
        .bus_role = BUS_ROLE_MASTER ,
        .tx_mode = SPI_TX_FULL_DUPLEX ,
        .move_mode = MOVE_MODE_DMA ,
        .direction = SPI_DIRECTION_2WIRES ,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_CLK_IDLE_LEVEL_0,
        .irq_priority = 1,
        .interrupt_on = true,

        .DmaChTx = {.dma_num = 1, .stream = 4, .channel = 0, .name = "SPI2_TX",},
        .DmaChRx = {.dma_num = 1, .stream = 3, .channel = 0, .name = "SPI2_RX",},

        .dma_channel_tx_num = DMA_CHANNEL_NUM_SPI2_TX,
        .dma_channel_rx_num = DMA_CHANNEL_NUM_SPI2_RX,

        .PadSck = {  .port = PORT_B, .pin = 10, },
        .PadMosi = { .port = PORT_C, .pin = 3, },
        .PadMiso = { .port = PORT_C, .pin = 2, },
    },
#endif
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI2
    { .num = 2, .valid = true, },
#endif
};

COMPONENT_GET_CNT(Spi, spi)
