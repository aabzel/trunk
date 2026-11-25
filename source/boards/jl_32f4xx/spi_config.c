#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif

#include "data_utils.h"
#include "spi_types.h"


#ifdef HAS_SPI1_DMA
#define SPI_DMA_CONFIG_SPI1                                                             \
        .dma_channel_tx_num = DMA_CHANNEL_NUM_SPI1_TX,                                  \
        .dma_channel_rx_num = DMA_CHANNEL_NUM_SPI1_RX,                                  \
        .DmaChRx = { .name="SPI1_RX",  .priority=1, .dma_num=, .stream=,  .channel=,},  \
        .DmaChTx = { .name="SPI1_TX",  .priority=1, .dma_num=, .stream=,  .channel=,},
#else
#define SPI_DMA_CONFIG_SPI1
#endif


#ifdef HAS_SPI3_DMA
#define SPI_DMA_CONFIG_SPI3                                         \
        .dma_channel_tx_num = DMA_CHANNEL_NUM_SPI3_TX,                     \
        .dma_channel_rx_num = DMA_CHANNEL_NUM_SPI3_RX,                     \
        .DmaChRx = { .name="SPI3_RX",  .priority=1, .dma_num=1, .stream=0,  .channel=0,},                     \
        .DmaChTx = { .name="SPI3_TX",  .priority=1, .dma_num=1, .stream=5,  .channel=0,},
#else
#define SPI_DMA_CONFIG_SPI3
#endif

#ifdef HAS_SPI1
#define SPI_CONFIG_SPI1                              \
    {                                                \
        .num = 1,                                    \
        .name = "ili9341",                           \
        .bit_rate_hz = 2000000,                      \
        .bit_order = BIT_ORDER_MSB ,                 \
        .bus_role = IF_BUS_ROLE_MASTER ,             \
        .direction =  SPI_DIRECTION_2WIRES ,         \
        .frame_size =  8,                            \
        .tx_mode = SPI_TX_FULL_DUPLEX ,              \
        .move_mode = MOVE_MODE_INTERRUPT ,           \
        .polarity =  SPI_POLARITY_LATCH_RISING ,     \
        .phase =  SPI_CLK_IDLE_LEVEL_0 ,             \
        .chip_select = SPI_CHIP_SEL_SW ,             \
        .interrupt_on = true,                        \
        .irq_priority =  0,                          \
        .valid = true,                               \
        .PadCs = {.port = PORT_A, .pin = 3, },       \
        .PadSck = {.port=PORT_A, .pin=5,},           \
        .PadMiso = {.port=PORT_A, .pin=6,},          \
        .PadMosi = {.port=PORT_A, .pin=7,},          \
        .GpioRxDebug = {.port=PORT_F, .pin=9,},      \
        .GpioTxDebug = {.port=PORT_F, .pin=10,},     \
        SPI_DMA_CONFIG_SPI1                          \
    },
#else
#define SPI_CONFIG_SPI1
#endif


#ifdef HAS_SPI3
#define SPI_CONFIG_SPI3                              \
    {                                                \
        .num = 3,                                    \
        .name = "w25q16jv",                          \
        .bit_rate_hz = 50000000,                     \
        .bit_order = BIT_ORDER_MSB ,                 \
        .bus_role = IF_BUS_ROLE_MASTER ,             \
        .direction =  SPI_DIRECTION_2WIRES ,         \
        .frame_size =  8 ,                           \
        .tx_mode = SPI_TX_FULL_DUPLEX ,              \
        .move_mode = MOVE_MODE_INTERRUPT ,           \
        .polarity =  SPI_POLARITY_LATCH_RISING ,     \
        .phase =  SPI_CLK_IDLE_LEVEL_1 ,             \
        .chip_select = SPI_CHIP_SEL_SW ,             \
        .interrupt_on = true ,                       \
        .irq_priority =  0 ,                         \
        .valid = true,                               \
        .PadCs = {.port = PORT_B, .pin = 14, },      \
        .PadSck = {.port=PORT_B, .pin=3,},           \
        .PadMiso = {.port=PORT_B, .pin=4,},          \
        .PadMosi = {.port=PORT_B, .pin=5,},          \
        .GpioRxDebug = {.port=PORT_F, .pin=9,},      \
        .GpioTxDebug = {.port=PORT_F, .pin=10,},     \
        SPI_DMA_CONFIG_SPI3                          \
    },
#else
#define SPI_CONFIG_SPI3
#endif

const SpiConfig_t SpiConfig[] = {
        SPI_CONFIG_SPI1
        SPI_CONFIG_SPI3

#ifdef HAS_SPI2
    {
        .num = 2,
        .name = "GamePadPS2",
        .bit_rate_hz = 250000,
        .bus_role = BUS_ROLE_MASTER ,
        .frame_size =  8 ,
        .tx_mode = SPI_TX_FULL_DUPLEX ,
        .move_mode = MOVE_MODE_INTERRUPT ,
        .bit_order = BIT_ORDER_LSB ,
        .polarity =  SPI_POLARITY_LATCH_FALING ,
        .phase =  SPI_PHASE_1 ,
        .chip_select = SPI_CHIP_SEL_SW ,
        .interrupt_on = true ,
        .irq_priority =  0 ,
        .valid = true,
    },
#endif
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI1
    {.num = 1, .valid = true,},
#endif

#ifdef HAS_SPI2
    {.num = 2, .valid = true,},
#endif

#ifdef HAS_SPI3
    {.num = 3, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Spi, spi)
